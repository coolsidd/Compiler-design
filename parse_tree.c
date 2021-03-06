/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
*/

#include "parse_tree.h"
#include <stdio.h>
#define MAXRULES 100

Parse_tree_node *getNodeFromIndex(Parse_tree_node *p, int index)
{
    for(int i = 0; i < index; i++){
        p = p->next;
    }
    return p;
}

Parse_tree_node* createParseTree(TokenStream *s, Grammar *g, int *maxline){
    Symbol starting_symb;
    starting_symb.s = g->start_symb.s;
    starting_symb.is_terminal = false;
    return recursiveParseNonterminal(starting_symb, &(s->head), g, maxline, 0);
}

Parse_tree_node *recursiveParseNonterminal(Symbol symb, Token ** tstr, Grammar *g, int *maxline, int depth) {
    //printf("Trying to derive %s:\n", toStringSymbol(symb));
    Parse_tree_node * new_node = NULL;
    for(int i=0; i<g->num_rules; i++){

        if(g->rules[i].lhs.s == symb.s){
            ////printf("trying to apply rule no. %d\n", i);
            //printf("Trying \"%s -> ",toStringSymbol(g->rules[i].lhs) );
            /* for(RuleNode* check_rule = g->rules[i].rhs; check_rule; check_rule = check_rule->next){ */
            /*     //printf("%s ", toStringSymbol(check_rule->s)); */
            /* } */
            //printf("\"\n");

            bool flag_successful = true;
            Token *temp_tstr = *tstr;
            Token *tempToken = (Token*)malloc(sizeof(Token));
            tempToken->token_name = toStringSymbol(symb);
            tempToken->lexeme = symb;
            tempToken->line_no = -1;
            tempToken->next = NULL;
            Parse_tree_node* new_node = new_parse_tree(tempToken);
            new_node->depth = depth;


            for(RuleNode* check_rule = g->rules[i].rhs; check_rule; check_rule = check_rule->next){
                if(check_rule->s.is_terminal && temp_tstr->lexeme.is_terminal){
                    if(check_rule->s.s == temp_tstr->lexeme.s){
                        //printf("Found %s at line %d next\n", toStringSymbol(check_rule->s), temp_tstr->line_no);
                        Parse_tree_node *tempChildNode = new_parse_tree(temp_tstr);
                        tempChildNode->depth = depth+1;
                        add_parsed_child(new_node, tempChildNode);
                        temp_tstr = temp_tstr->next;
                        continue;
                    }
                    else{
                        //printf("Expected %s found %s at line %d\n", toStringSymbol(check_rule->s), temp_tstr->token_name, temp_tstr->line_no);
                        flag_successful = false;
                        break;
                    }
                }else if(!(check_rule->s.is_terminal)){
                    Parse_tree_node *tempChildNode = recursiveParseNonterminal(check_rule->s, &temp_tstr, g, maxline, depth+1);
                    if(tempChildNode){
                        add_parsed_child(new_node, tempChildNode);
                    }else{
                        //printf("%s failed \n", toStringSymbol(check_rule->s));
                        flag_successful = false;
                        break;
                    }
                }else{
                    //printf("Expected %s found %s at line %d\n", toStringSymbol(check_rule->s), temp_tstr->token_name, temp_tstr->line_no);
                    flag_successful = false;
                    break;
                }
            }
            if(flag_successful){
                //printf("%s successfully derived\n", toStringSymbol(symb));
                if(temp_tstr){
                    //printf("Parsing till line %d done\n", temp_tstr->line_no);
                    if (temp_tstr->line_no > *maxline) *maxline = temp_tstr->line_no;
                    *tstr = temp_tstr;
                }
                return new_node;
            }else{
                free(tempToken);
                free_parse_tree(new_node);
                continue;
            }
        }
    }
    //printf("Failed to derive %s\n", toStringSymbol(symb));
    return NULL;
}

Parse_tree_node* new_parse_tree(Token *tok){
    Parse_tree_node* new_tree = (Parse_tree_node*)malloc(sizeof(Parse_tree_node));
    new_tree->num_children=0;
    new_tree->child = NULL;
    new_tree->last_child = NULL;
    new_tree->next = NULL;
    new_tree->tok = tok;
    new_tree->parent = NULL;
    new_tree->txp = NULL;
    return new_tree;
}
void free_parse_tree(Parse_tree_node *root){


    Parse_tree_node* temp =  root->child;
    while(temp){
        root->child = root->child->next;
        free_parse_tree(temp);
        temp = root->child;
    }
    /* while(temp){ */
    /*     root->child = root->child->next; */
    /*     free_parse_tree(temp); */
    /*     temp = root->child; */
    /*     //root->num_children--; */
    /* } */
    /* if(root->tok) */
    /*     free(root->tok); */
    //root->tok = NULL;
    free (root);
    return ;
}
void add_parsed_child(Parse_tree_node *root, Parse_tree_node *node){
    //printf("Adding child %s -> %s\n",toStringSymbol(root->tok->lexeme), toStringSymbol(node->tok->lexeme));
    if(!root->child){
        node->parent = root;
        root->child = node;
        root->last_child = node;
        root->num_children = 1;
        return;
    }
    node->parent = root;
    root->last_child->next = node;
    root->num_children++;
    root->last_child = root->last_child->next;
    return;
}

#include "parse_tree.h"
#include "util/output_file_structs.h"
#include <stdlib.h>

void createParseTree(Parse_tree_node* t, TokenStream *s, Grammar *g){
    Symbol starting_symb;
    starting_symb.s = program;
    starting_symb.is_terminal = false;
    recursiveParseNonterminal(starting_symb, &s, g);
}

Parse_tree_node *recursiveParseNonterminal(Symbol symb, Token ** tstr, Grammar *g){
    printf("Trying to derive %s\n", toStringSymbol(symb));
    Parse_tree_node * new_node = NULL;
    for(int i=0; i<g->num_rules; i++){
        if(g->rules[i].lhs.s == symb.s){

            bool flag_successful = true;
            Token *temp_tstr = *tstr;
            Token *tempToken = (Token*)malloc(sizeof(Token));
            tempToken->token_name = toStringSymbol(symb);
            tempToken->lexeme = symb;
            tempToken->line_no = -1;
            tempToken->next = NULL;
            Parse_tree_node* new_node = new_parse_tree(tempToken);


            for(RuleNode* check_rule = g->rules[i].rhs; check_rule; check_rule = check_rule->next){
                if(check_rule->s.is_terminal && temp_tstr->lexeme.is_terminal){
                    if(check_rule->s.s == temp_tstr->lexeme.s){
                        Parse_tree_node *tempChildNode = new_parse_tree(temp_tstr);
                        add_parsed_child(new_node, tempChildNode);
                        temp_tstr = temp_tstr->next;
                        continue;
                    }
                    else{
                        flag_successful = false;
                        break;
                    }
                }else if(!(check_rule->s.is_terminal)){
                    Parse_tree_node *tempChildNode = recursiveParseNonterminal(check_rule->s, &temp_tstr, g);
                    if(tempChildNode){
                        add_parsed_child(new_node, tempChildNode);
                    }else{
                        flag_successful = false;
                        break;
                    }
                }
            }
            if(flag_successful){
                printf("%s successfully derived\n", toStringSymbol(symb));
                *tstr = temp_tstr;
                return new_node;
            }else{
                free(tempToken);
                free_parse_tree(new_node);
                continue;
            }
        }
    }
    printf("Failed to derive %s", toStringSymbol(symb));
    return new_node;
}

Parse_tree_node* new_parse_tree(Token *tok){
    Parse_tree_node* new_tree = (Parse_tree_node*)malloc(sizeof(Parse_tree_node));
    new_tree->num_children=0;
    new_tree->child = NULL;
    new_tree->last_child = NULL;
    new_tree->next = NULL;
    new_tree->tok = tok;
    return new_tree;
}
void free_parse_tree(Parse_tree_node *root){
    // TODO : Free tree
    //
    printf("WIP!ERROR\nERROR\n");
    return ;
}
void add_parsed_child(Parse_tree_node *root, Parse_tree_node *node){
    if(!root->child){
        root->child = node;
        root->last_child = node;
        root->num_children = 1;
        return;
    }
    root->last_child->next = node;
    root->num_children++;
    return;
}


int main(){
    return 0;
}

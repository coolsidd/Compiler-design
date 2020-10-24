#include "parse_tree.h"
#include <stdio.h>

Parse_tree_node* createParseTree(TokenStream *s, Grammar *g){
    Symbol starting_symb;
    starting_symb.s = main_program;
    starting_symb.is_terminal = false;
    return recursiveParseNonterminal(starting_symb, &(s->head), g);
}

Parse_tree_node *recursiveParseNonterminal(Symbol symb, Token ** tstr, Grammar *g){
    printf("Trying to derive %s\n", toStringSymbol(symb));
    Parse_tree_node * new_node = NULL;
    for(int i=0; i<g->num_rules; i++){

        if(g->rules[i].lhs.s == symb.s){
            //printf("trying to apply rule no. %d\n", i);
            printf("Trying \"%s -> ",toStringSymbol(g->rules[i].lhs) );
            for(RuleNode* check_rule = g->rules[i].rhs; check_rule; check_rule = check_rule->next){
                printf("%s ", toStringSymbol(check_rule->s));
            }
            printf("\"\n");

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
                        printf("Found %s at line %d next\n", toStringSymbol(check_rule->s), temp_tstr->line_no);
                        Parse_tree_node *tempChildNode = new_parse_tree(temp_tstr);
                        add_parsed_child(new_node, tempChildNode);
                        temp_tstr = temp_tstr->next;
                        continue;
                    }
                    else{
                        printf("Expected %s found %s at line %d\n", toStringSymbol(check_rule->s), temp_tstr->token_name, temp_tstr->line_no);
                        flag_successful = false;
                        break;
                    }
                }else if(!(check_rule->s.is_terminal)){
                    Parse_tree_node *tempChildNode = recursiveParseNonterminal(check_rule->s, &temp_tstr, g);
                    if(tempChildNode){
                        add_parsed_child(new_node, tempChildNode);
                    }else{
                        printf("%s failed \n", toStringSymbol(check_rule->s));
                        flag_successful = false;
                        break;
                    }
                }
            }
            if(flag_successful){
                printf("%s successfully derived\n", toStringSymbol(symb));
                printf("Parsing till line %d done\n", temp_tstr->line_no);
                *tstr = temp_tstr;
                return new_node;
            }else{
                free(tempToken);
                free_parse_tree(new_node);
                continue;
            }
        }
    }
    printf("Failed to derive %s\n", toStringSymbol(symb));
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

    Parse_tree_node* temp =  root->child;

    while(temp){
        root->child = root->child->next;
        free_parse_tree(temp);
        temp = root->child;
        root->num_children--;
    }
    //free(root->tok);
    free (root);
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

/* int main(int argc, char** argv){ */
/*     Grammar* g = (Grammar*)malloc(sizeof(Grammar)); */
/*     g->num_rules = 0; */
/*     g->start_symb = toSymbol("main_program"); */
/*     g->rules = (Rule*)malloc(MAXRULES*sizeof(Rule)); */
/*     readGrammar("./util/grammar.out", g); */
/*     printGrammar(g); */
/*     TokenStream *s = newTokenStream(); */
/*     tokenizeSourceCode(argv[1], s); */
/*     /\* for(Token *temp = s->head; temp; temp=temp->next){ *\/ */
/*     /\*      printSymbol(temp->lexeme); *\/ */
/*     /\* } *\/ */
/*     Parse_tree_node * p; */
/*     p = createParseTree(s,g); */

/*     return 0; */
/* } */

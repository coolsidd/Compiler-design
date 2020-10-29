/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
*/

#include "linked_list.h"

linked_list *create_linked_list()
{
    linked_list *ll = calloc(1, sizeof(linked_list));
    ll->num_nodes = 0;
    ll->head = NULL;
    ll->tail = NULL;
    return ll;
}

void ll_add_at(linked_list *ll, void *data, int idx)
{
    assert(idx <= ll->num_nodes && idx >= 0, "linked list insertion index valid");

    ll_node *new_node = calloc(1, sizeof(ll_node));
    new_node->data = data;

    if (ll->num_nodes == 0)
    {
        new_node->next = NULL;
        new_node->prev = NULL;
        ll->head = new_node;
        ll->tail = new_node;
        ll->num_nodes = 1;
    }
    else
    {
        if (idx == 0)
        {
            new_node->next = ll->head;
            ll->head->prev = new_node;
            new_node->prev = NULL;
            ll->head = new_node;
            (ll->num_nodes)++;
        }
        else if (idx == ll->num_nodes)
        {
            ll->tail->next = new_node;
            new_node->prev = ll->tail;
            new_node->next = NULL;
            ll->tail = new_node;
            (ll->num_nodes)++;
        }
        else
        {
            ll_node *temp;
            ll_node *pre_temp;
            pre_temp = ll->head;
            temp = pre_temp->next;
            int i = 1;
            while (i < idx)
            {
                temp = temp->next;
                pre_temp = pre_temp->next;
                i++;
            }
            pre_temp->next = new_node;
            temp->prev = new_node;
            new_node->next = temp;
            new_node->prev = pre_temp;
            (ll->num_nodes)++;
        }
    }
}

void ll_append(linked_list *ll, void *data)
{
    ll_add_at(ll, data, ll->num_nodes);
}

void *ll_get(linked_list *ll, int idx)
{
    assert(idx < ll->num_nodes && idx >= 0, "index valid while getting from linked list");

    if (idx == 0)
    {
        return ll->head->data;
    }
    else if (idx == ll->num_nodes - 1)
    {
        return ll->tail->data;
    }
    else
    {
        int i = 0;
        ll_node *temp = ll->head;
        while (i < idx)
        {
            temp = temp->next;
            i++;
        }
        return temp->data;
    }
}

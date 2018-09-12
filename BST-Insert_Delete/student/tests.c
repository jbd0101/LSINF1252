/*
 * 7/7 tests on insert (need the fail malloc + fail malloc with null tree ? il faudrait free le tree du coup ? too hard ?). Question on NULL tree test.
 * 1/1 test on right subtree's leftmost node
 * 7/8-9 tests on delete (need the biggest one, using right subtree's leftmost node)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "student_code.h"
#include "CTester/CTester.h"

int sameNodes(node_t* node1, node_t* node2){
    if(node1 == NULL && node2 == NULL)
        return true;
    if(node1 == NULL || node2 == NULL)
        return false;
    if(strcmp(node1->enWord, node2->enWord) || strcmp(node1->frWord, node2->frWord))
        return false;
    return sameNodes(node1->left, node2->left) && sameNodes(node1->right, node2->right);
}

int sameTrees(bt_t* solT, bt_t* tree){
    if(solT == NULL && tree == NULL)
        return true;
    if(solT == NULL || tree == NULL)
        return false;
    return sameNodes(solT->root, tree->root);
}

void freeNode(node_t* node){
    if(!node)
        return;
    if(node->enWord)
        free(node->enWord);
    if(node->frWord)
        free(node->frWord);
    if(node->left)
        freeNode(node->left);
    if(node->right)
        freeNode(node->right);
    free(node);
}

node_t* init_node(char* enWord, char* frWord){
    node_t* newnode = malloc(sizeof(node_t));
    if(!newnode)
        return NULL;
    newnode->enWord = (char*) malloc(sizeof(char)*(strlen(enWord)+1));
    if(!(newnode->enWord)){
        free(newnode);
        return NULL;
    }
    strcpy(newnode->enWord,enWord);
    newnode->frWord = (char*) malloc(sizeof(char)*(strlen(frWord)+1));
    if(!(newnode->frWord)){
        free(newnode->enWord);
        free(newnode);
        return NULL;
    }
    strcpy(newnode->frWord,frWord);
    newnode->left = newnode->right = NULL;
    return newnode;
}

void freeBt(bt_t* bt){
    if(!bt)
        return;
    if(bt->root)
        freeNode(bt->root);
}

bt_t* init_bt(char* enWord, char* frWord){
    node_t* root = init_node(enWord,frWord);
    if(!root)
        return NULL;
    bt_t* bt = (bt_t*) malloc(sizeof(bt_t));
    if(!bt){
        freeNode(bt->root);
        return NULL;
    }
    bt->root = root;
    return bt;
}

bt_t* tree1(){
    bt_t* tree = init_bt("cat","chat");
    if(!tree)
        CU_FAIL(_("Internal error while allocating memory"));
    node_t* node1 = init_node("animal","animal");
    node_t* node2 = init_node("deer","biche");
    node_t* node3 = init_node("creature","créature");
    node_t* node4 = init_node("elephant","éléphant");
    node_t* node5 = init_node("dog","chien");
    node_t* node6 = init_node("eagle","aigle");
    node_t* node7 = init_node("sponge","éponge");

    if(!node1 || !node2 || !node3 || !node4 || !node5 || !node6 || !node7){
        freeNode(tree->root);
        if(node1) freeNode(node1);
        if(node2) freeNode(node2);
        if(node3) freeNode(node3);
        if(node4) freeNode(node4);
        if(node5) freeNode(node5);
        if(node6) freeNode(node6);
        if(node7) freeNode(node7);
        free(tree);
        CU_FAIL(_("Internal error while allocating memory"));
    }
    else{
        (tree->root)->left = node1; (tree->root)->right = node2;
        node2->left = node3; node2->right = node4;
        node4->left = node5; node4->right = node7;
        node5->right = node6;
    }
    return tree;
}

bt_t* tree2(){
    bt_t* tree = init_bt("cat","chat");
    if(!tree)
        CU_FAIL(_("Internal error while allocating memory"));
    node_t* node1 = init_node("animal","animal");
    node_t* node2 = init_node("deer","biche");
    node_t* node3 = init_node("creature","créature");
    node_t* node4 = init_node("horse","cheval");
    node_t* node5 = init_node("dog","chien");
    node_t* node6 = init_node("eagle","aigle");
    node_t* node7 = init_node("sponge","éponge");
    node_t* node8 = init_node("dodo","dodo");
    node_t* node9 = init_node("fish","poisson");
    node_t* node10 = init_node("falcon","faucon");

    if(!node1 || !node2 || !node3 || !node4 || !node5 || !node6 || !node7 || !node8 ||!node9){
        freeNode(tree->root);
        if(node1) freeNode(node1);
        if(node2) freeNode(node2);
        if(node3) freeNode(node3);
        if(node4) freeNode(node4);
        if(node5) freeNode(node5);
        if(node6) freeNode(node6);
        if(node7) freeNode(node7);
        if(node8) freeNode(node8);
        if(node9) freeNode(node9);
        free(tree);
        CU_FAIL(_("Internal error while allocating memory"));
    }
    else{
        // = NULL done in init_node
        (tree->root)->left = node1; (tree->root)->right = node2;
        node2->left = node3; node2->right = node4;
        node4->left = node5; node4->right = node7;
        node5->left = node8; node5->right = node6;
        node6->right = node9;
        node9->left = node10;
    }
    return tree;
}

bt_t* tree3(){
    bt_t* tree = init_bt("cat","chat");
    if(!tree)
        CU_FAIL(_("Internal error while allocating memory"));
    node_t* node1 = init_node("animal","animal");

    if(!node1){
        freeNode(tree->root);
        if(node1) freeNode(node1);
        free(tree);
        CU_FAIL(_("Internal error while allocating memory"));
    }
    else{
        // = NULL done in init_node
        (tree->root)->left = node1;
    }
    return tree;
}

bt_t* tree4(){
    bt_t* tree = init_bt("cat","chat");
    if(!tree)
        CU_FAIL(_("Internal error while allocating memory"));
    node_t* node1 = init_node("animal","animal");
    node_t* node2 = init_node("deer","biche");
    node_t* node3 = init_node("creature","créature");
    node_t* node4 = init_node("elephant","éléphant");
    node_t* node7 = init_node("sponge","éponge");

    if(!node1 || !node2 || !node3 || !node4 || !node7){
        freeNode(tree->root);
        if(node1) freeNode(node1);
        if(node2) freeNode(node2);
        if(node3) freeNode(node3);
        if(node4) freeNode(node4);
        if(node7) freeNode(node7);
        free(tree);
        CU_FAIL(_("Internal error while allocating memory"));
    }
    else{
        (tree->root)->left = node1; (tree->root)->right = node2;
        node2->left = node3; node2->right = node4;
        node4->right = node7;
    }
    return tree;
}

void test_insert_normal(){
    set_test_metadata("insert", _("Test in a normal case"), 1);
    bt_t* tree = tree1();
    char* newEnWord = malloc(sizeof(char)*5);
    char* newFrWord = malloc(sizeof(char)*5);

    bt_t* solT = tree1();

    if(!newEnWord || !newFrWord || !tree || !solT){
        if(newEnWord)
            free(newEnWord);
        if(newFrWord)
            free(newFrWord);
        if(tree){
            freeNode(tree->root);
            free(tree);
        }
        if(solT){
            freeNode(solT->root);
            free(solT);
        }
        CU_FAIL(_("Internal error while allocating memory"));
        //TODO return ??? Or CU_FAIL is enough ?
    }
    
    strcpy(newEnWord, "dodo");
    strcpy(newFrWord, "dodo");

    monitored.malloc = true;
    int inserted;
    SANDBOX_BEGIN;
    inserted = insert(tree, newEnWord, newFrWord);
    SANDBOX_END;

    newEnWord = realloc(newEnWord, sizeof(char)*8);
    strcpy(newEnWord, "changed");
    
    // check if only 3 malloc (enWord, frWord, node);
    int nbMalloc = stats.malloc.called;
    CU_ASSERT_EQUAL(nbMalloc, 3);
    if(nbMalloc != 3)
        push_info_msg(_("You can only use 3 calls to malloc for this case"));
    //TODO Hard coded feature ? better to compare with a real tree ?
    //It takes more time but we can be sure of the answer with that...
    //'dodo' place was hardcoded, should we use our own function to insert it ?
    ((((solT->root)->right)->right)->left)->left = init_node("dodo","dodo");
    int sameT = sameTrees(solT,tree);
    CU_ASSERT_EQUAL(sameT,true);
    if(!sameT)
        push_info_msg(_("Your tree isn't what was expected"));

    CU_ASSERT_EQUAL(inserted, 1);
    if(inserted != 1)
        push_info_msg(_("The returned value should be 1"));
}

void test_insert_normal_first_malloc_fails(){
    set_test_metadata("insert", _("Test when malloc fails"), 1);
    bt_t* tree = tree1();
    char* newEnWord = malloc(sizeof(char)*5);
    char* newFrWord = malloc(sizeof(char)*5);

    bt_t* solT = tree1();

    if(!newEnWord || !newFrWord || !tree || !solT){
        if(newEnWord)
            free(newEnWord);
        if(newFrWord)
            free(newFrWord);
        if(tree){
            freeNode(tree->root);
            free(tree);
        }
        if(solT){
            freeNode(solT->root);
            free(solT);
        }
        CU_FAIL(_("Internal error while allocating memory"));
        //TODO return ??? Or CU_FAIL is enough ?
    }
    
    strcpy(newEnWord, "dodo");
    strcpy(newFrWord, "dodo");
    
    failures.malloc = FAIL_FIRST;
    monitored.malloc = true;
    monitored.free = true;
    int inserted;
    SANDBOX_BEGIN;
    inserted = insert(tree, newEnWord, newFrWord);
    SANDBOX_END;

    // check if only 1 malloc (enWord, frWord, node) since it fails.
    int nbMalloc = stats.malloc.called;
    CU_ASSERT_EQUAL(nbMalloc, 1);
    if(nbMalloc != 1)
        push_info_msg(_("You should have used malloc only once in this case"));
    
    int nbFree = stats.free.called;
    CU_ASSERT_EQUAL(nbFree, 0);
    if(nbFree != 0)
        push_info_msg(_("You shouldn't have called free"));
    
    int sameT = sameTrees(solT,tree);
    CU_ASSERT_EQUAL(sameT,true);
    if(!sameT)
        push_info_msg(_("Your tree isn't what was expected"));

    CU_ASSERT_EQUAL(inserted, 0);
    if(inserted != 0)
        push_info_msg(_("The returned value should be 0"));
}

void test_insert_normal_second_malloc_fails(){
    set_test_metadata("insert", _("Test when second malloc fails"), 1);
    bt_t* tree = tree1();
    char* newEnWord = malloc(sizeof(char)*5);
    char* newFrWord = malloc(sizeof(char)*5);

    bt_t* solT = tree1();

    if(!newEnWord || !newFrWord || !tree || !solT){
        if(newEnWord)
            free(newEnWord);
        if(newFrWord)
            free(newFrWord);
        if(tree){
            freeNode(tree->root);
            free(tree);
        }
        if(solT){
            freeNode(solT->root);
            free(solT);
        }
        CU_FAIL(_("Internal error while allocating memory"));
        //TODO return ??? Or CU_FAIL is enough ?
    }
    
    strcpy(newEnWord, "dodo");
    strcpy(newFrWord, "dodo");
    
    failures.malloc = FAIL_SECOND;
    monitored.malloc = true;
    monitored.free = true;
    int inserted;
    SANDBOX_BEGIN;
    inserted = insert(tree, newEnWord, newFrWord);
    SANDBOX_END;

    // check if only 2 malloc (enWord, frWord, node) since the second one fails.
    int nbMalloc = stats.malloc.called;
    CU_ASSERT_EQUAL(nbMalloc, 2);
    if(nbMalloc != 2)
        push_info_msg(_("You should have used malloc only twice in this case"));
    
    int nbFree = stats.free.called;
    CU_ASSERT_EQUAL(nbFree, 1);
    if(nbFree != 1)
        push_info_msg(_("You should have called free once"));
    
    int sameT = sameTrees(solT,tree);
    CU_ASSERT_EQUAL(sameT,true);
    if(!sameT)
        push_info_msg(_("Your tree isn't what was expected"));

    CU_ASSERT_EQUAL(inserted, 0);
    if(inserted != 0)
        push_info_msg(_("The returned value should be 0"));
}

void test_insert_normal_third_malloc_fails(){
    set_test_metadata("insert", _("Test when third malloc fails"), 1);
    bt_t* tree = tree1();
    char* newEnWord = malloc(sizeof(char)*5);
    char* newFrWord = malloc(sizeof(char)*5);

    bt_t* solT = tree1();

    if(!newEnWord || !newFrWord || !tree || !solT){
        if(newEnWord)
            free(newEnWord);
        if(newFrWord)
            free(newFrWord);
        if(tree){
            freeNode(tree->root);
            free(tree);
        }
        if(solT){
            freeNode(solT->root);
            free(solT);
        }
        CU_FAIL(_("Internal error while allocating memory"));
        //TODO return ??? Or CU_FAIL is enough ?
    }
    
    strcpy(newEnWord, "dodo");
    strcpy(newFrWord, "dodo");
    
    failures.malloc = FAIL_THIRD;
    monitored.malloc = true;
    monitored.free = true;
    int inserted;
    SANDBOX_BEGIN;
    inserted = insert(tree, newEnWord, newFrWord);
    SANDBOX_END;

    // check if only 3 malloc (enWord, frWord, node)
    int nbMalloc = stats.malloc.called;
    CU_ASSERT_EQUAL(nbMalloc, 3);
    if(nbMalloc != 3)
        push_info_msg(_("You should have used malloc only three times in this case"));
    
    int nbFree = stats.free.called;
    CU_ASSERT_EQUAL(nbFree, 2);
    if(nbFree != 2)
        push_info_msg(_("You should have called free twice"));
    
    int sameT = sameTrees(solT,tree);
    CU_ASSERT_EQUAL(sameT,true);
    if(!sameT)
        push_info_msg(_("Your tree isn't what was expected"));

    CU_ASSERT_EQUAL(inserted, 0);
    if(inserted != 0)
        push_info_msg(_("The returned value should be 0"));
}

void test_insert_empty_tree(){
    set_test_metadata("insert", _("Test with an empty tree"),1);
    //student arguments
    bt_t* tree = malloc(sizeof(bt_t));
    tree->root = NULL;
    bt_t *solT = init_bt("dodo","dodo");
    char* newEnWord = malloc(sizeof(char)*5);
    char* newFrWord = malloc(sizeof(char)*5);

    //solution
    if(!newEnWord || !newFrWord || !tree || !solT){
        if(newEnWord)
            free(newEnWord);
        if(newFrWord)
            free(newFrWord);
        if(tree)
            free(tree);
        if(solT){
            freeNode(solT->root);
            free(solT);
        }
        CU_FAIL(_("Internal error while allocating memory"));
        //TODO return ??? Or CU_FAIL is enough ?
    }
    
    strcpy(newEnWord, "dodo");
    strcpy(newFrWord, "dodo");
    
    monitored.malloc = true;
    int inserted;
    SANDBOX_BEGIN;
    inserted = insert(tree, newEnWord, newFrWord);
    SANDBOX_END;

    // check if only 3 malloc (enWord, frWord, node);
    int nbMalloc = stats.malloc.called;
    CU_ASSERT_EQUAL(nbMalloc, 3);
    if(nbMalloc != 3)
        push_info_msg(_("You can only use 3 calls to malloc for this case"));

    int sameT = sameTrees(solT,tree);
    CU_ASSERT_EQUAL(sameT,true);
    if(!sameT)
        push_info_msg(_("Your tree isn't what was expected"));

    CU_ASSERT_EQUAL(inserted, 1);
    if(inserted != 1)
        push_info_msg(_("The returned value should be 1"));
}

void test_insert_already_inserted(){
    set_test_metadata("insert", _("Test with an already inserted node"),1);
    //student arguments
    bt_t* tree = tree1();
    char* newEnWord = malloc(sizeof(char)*4);
    char* newFrWord = malloc(sizeof(char)*5);

    //solution
    bt_t* solT = tree1();

    if(!newEnWord || !newFrWord || !tree || !solT){
        if(newEnWord)
            free(newEnWord);
        if(newFrWord)
            free(newFrWord);
        if(tree){
            freeNode(tree->root);
            free(tree);
        }
        if(solT){
            freeNode(solT->root);
            free(solT);
        }
        CU_FAIL(_("Internal error while allocating memory"));
        //TODO return ??? Or CU_FAIL is enough ?
    }
    
    strcpy(newEnWord, "cat");
    strcpy(newFrWord, "chat");
    
    monitored.malloc = true;
    monitored.free = true;
    int inserted;
    SANDBOX_BEGIN;
    inserted = insert(tree, newEnWord, newFrWord);
    SANDBOX_END;

    //TODO : on pourrait check la mémoire aussi mais s'il malloc puis free, il aura bon donc que faire?
    // Check : 0 malloc, 0 free
    int nbMalloc = stats.malloc.called;
    CU_ASSERT_EQUAL(nbMalloc, 0);
    if(nbMalloc != 0)
        push_info_msg(_("You can't use malloc in this case"));

    int nbFree = stats.malloc.called;
    CU_ASSERT_EQUAL(nbFree, 0);
    if(nbFree != 0)
        push_info_msg(_("Why did you use free ?"));

    int sameT = sameTrees(solT,tree);
    CU_ASSERT_EQUAL(sameT,true);
    if(!sameT)
        push_info_msg(_("Your tree isn't what was expected"));

    CU_ASSERT_EQUAL(inserted, 0);
    if(inserted != 0)
        push_info_msg(_("The returned value should be 0"));
}

void test_delete_no_child(){
    set_test_metadata("delete", _("Test with a node having no child"),1);
    //student arguments
    bt_t* tree = tree1();
    char *enWord = "eagle";

    bt_t* solT = tree1();

    if(!tree || !solT){
        if(tree){
            freeNode(tree->root);
            free(tree);
        }
        if(solT){
            freeNode(solT->root);
            free(solT);
        }
        CU_FAIL(_("Internal error while allocating memory"));
        //TODO return ??? Or CU_FAIL is enough ?
    }

    freeNode(((((solT->root)->right)->right)->left)->right);
    ((((solT->root)->right)->right)->left)->right = NULL;
    //TODO special feedback in case he free's but doesn't put NULL instead ?

    //TODO monitored malloc to see he isn't doing anything wrong ?
    monitored.free = true;
    SANDBOX_BEGIN;
    delete(tree,enWord);
    SANDBOX_END;

    int nbFree = stats.free.called;
    CU_ASSERT_EQUAL(nbFree, 3);
    if(nbFree != 3)
        push_info_msg(_("Wrong number of free's"));

    int sameT = sameTrees(solT,tree);
    CU_ASSERT_EQUAL(sameT,true);
    if(!sameT)
        push_info_msg(_("Your tree isn't what was expected"));

}

void test_delete_one_child(){
    set_test_metadata("delete", _("Test with a node having only one child"),1);
    //student arguments
    bt_t* tree = tree1();
    char* enWord = "dog";

    //solution
    bt_t* solT = tree1();

    if(!tree || !solT){
        if(tree){
            freeNode(tree->root);
            free(tree);
        }
        if(solT){
            freeNode(solT->root);
            free(solT);
        }
        CU_FAIL(_("Internal error while allocating memory"));
        //TODO return ??? Or CU_FAIL is enough ?
    }
    
    node_t* elephant = ((solT->root)->right)->right;
    node_t* dog = elephant->left;
    elephant->left = dog->right;
    free(dog->enWord);
    free(dog->frWord);
    free(dog);

    monitored.free = true;
    SANDBOX_BEGIN;
    delete(tree,enWord);
    SANDBOX_END;

    int nbFree = stats.free.called;
    CU_ASSERT_EQUAL(nbFree, 3);
    if(nbFree != 3)
        push_info_msg(_("Wrong number of free's"));

    int sameT = sameTrees(solT,tree);
    CU_ASSERT_EQUAL(sameT,true);
    if(!sameT)
        push_info_msg(_("Your tree isn't what was expected"));
}

void test_delete_node_not_found(){
    set_test_metadata("delete", _("Test with a key that isn't in the tree"),1);
    //student arguments
    bt_t* tree = tree1();
    char* enWord = "dodo";

    //solution
    bt_t* solT = tree1();

    if(!tree || !solT){
        if(tree){
            freeNode(tree->root);
            free(tree);
        }
        if(solT){
            freeNode(solT->root);
            free(solT);
        }
        CU_FAIL(_("Internal error while allocating memory"));
        //TODO return ??? Or CU_FAIL is enough ?
    }

    monitored.free = true;
    SANDBOX_BEGIN;
    delete(tree,enWord);
    SANDBOX_END;

    int nbFree = stats.free.called;
    CU_ASSERT_EQUAL(nbFree, 0);
    if(nbFree != 0)
        push_info_msg(_("Wrong number of free's"));

    int sameT = sameTrees(solT,tree);
    CU_ASSERT_EQUAL(sameT,true);
    if(!sameT)
        push_info_msg(_("Your tree isn't what was expected"));
}

void test_delete_root_replace_null(){
    set_test_metadata("delete", _("Test deleting the root of the tree, with no child"),1);
    //student arguments
    char* enWord = "dodo";
    char* frWord = "dodo";
    bt_t* tree = init_bt(enWord, frWord);

    //solution
    bt_t* solT = malloc(sizeof(bt_t));
    solT->root = NULL;

    if(!tree || !solT){
        if(tree){
            freeNode(tree->root);
            free(tree);
        }
        if(solT)
            free(solT);
        CU_FAIL(_("Internal error while allocating memory"));
        //TODO return ??? Or CU_FAIL is enough ?
    }

    monitored.free = true;
    SANDBOX_BEGIN;
    delete(tree,enWord);
    SANDBOX_END;

    int nbFree = stats.free.called;
    CU_ASSERT_EQUAL(nbFree, 3);
    if(nbFree != 3)
        push_info_msg(_("Wrong number of free's"));

    int sameT = sameTrees(solT,tree);
    CU_ASSERT_EQUAL(sameT,true);
    if(!sameT)
        push_info_msg(_("Your tree isn't what was expected"));

    //TODO special feedback in case he forgot to do bt->root = NULL ?
}

void test_delete_root_replace_node(){
    set_test_metadata("delete", _("Test deleting the root of the tree, with a child"),1);
    //student arguments
    bt_t* tree = tree3();
    char* enWord = "cat";
    
    //solution
    bt_t* solT = init_bt("animal","animal");

    if(!tree || !solT){
        if(tree){
            freeNode(tree->root);
            free(tree);
        }
        if(solT)
            free(solT);
        CU_FAIL(_("Internal error while allocating memory"));
        //TODO return ??? Or CU_FAIL is enough ?
    }

    monitored.free = true;
    SANDBOX_BEGIN;
    delete(tree,enWord);
    SANDBOX_END;

    int nbFree = stats.free.called;
    CU_ASSERT_EQUAL(nbFree, 3);
    if(nbFree != 3)
        push_info_msg(_("Wrong number of free's"));

    int sameT = sameTrees(solT,tree);
    CU_ASSERT_EQUAL(sameT,true);
    if(!sameT)
        push_info_msg(_("Your tree isn't what was expected"));
}

void test_delete_empty_tree(){
    set_test_metadata("delete", _("Test empty tree"),1);
    //student arguments
    char* enWord = "dodo";
    bt_t* tree = malloc(sizeof(bt_t));
    tree->root = NULL;

    //solution
    bt_t* solT = malloc(sizeof(bt_t));
    solT->root = NULL;

    if(!tree || !solT){
        if(tree)
            free(tree);
        if(solT)
            free(solT);
        CU_FAIL(_("Internal error while allocating memory"));
        //TODO return ??? Or CU_FAIL is enough ?
    }

    monitored.free = true;
    SANDBOX_BEGIN;
    delete(tree,enWord);
    SANDBOX_END;

    int nbFree = stats.free.called;
    CU_ASSERT_EQUAL(nbFree, 0);
    if(nbFree != 0)
        push_info_msg(_("Wrong number of free's"));

    int sameT = sameTrees(solT,tree);
    CU_ASSERT_EQUAL(sameT,true);
    if(!sameT)
        push_info_msg(_("Your tree isn't what was expected"));

}

// TEST TODO, hard to solve...
void test_delete_two_children_tree1(){
    set_test_metadata("delete", _("Test deleting a simple node (which has 2 children) using the algorithm explained above"),1);
    //student arguments
    bt_t* tree = tree1();
    bt_t* solT = tree1();
    
    if(!tree || !solT){
        if(tree){
            freeNode(tree->root);
            free(tree);
        }
        if(solT){
            freeNode(solT->root);
            free(solT);
        }
        CU_FAIL(_("Internal error while allocating memory"));
        //TODO return ??? Or CU_FAIL is enough ?
    }
    
    //sol
    node_t* deerdog = (solT->root)->right;
    free(deerdog->enWord); free(deerdog->frWord);
    node_t* dog = (deerdog->right)->left;
    deerdog->enWord = dog->enWord;
    deerdog->frWord = dog->frWord;
    node_t* elephant = deerdog->right;
    elephant->left = dog->right; //eagle
    free(dog);
    
    char* deerStr= "deer";
    
    monitored.malloc = true;
    monitored.free = true;
    SANDBOX_BEGIN;
    delete(tree, deerStr);
    SANDBOX_END;
    
    int nbMalloc = stats.malloc.called;
    int nbFree = stats.free.called;
    
    
    //TODO : you sould use free 3 times or wrong number of free's ?
    CU_ASSERT_EQUAL(nbFree,3);
    if(nbFree != 3){
        push_info_msg(_("You should use free 3 times"));
    }
    
    CU_ASSERT_EQUAL(nbMalloc,0);
    if(nbMalloc != 0){
        push_info_msg(_("Why are you using malloc ?"));
    }
    
    int sameT = sameTrees(solT,tree);
    CU_ASSERT_EQUAL(sameT,true);
    if(!sameT)
        push_info_msg(_("Your tree isn't what was expected"));
}

void test_delete_two_children_tree1_root(){
    set_test_metadata("delete", _("Test deleting the root node (which has 2 children) using the algorithm explained above"),1);
    //student arguments
    bt_t* tree = tree1();
    bt_t* solT = tree1();
    
    if(!tree || !solT){
        if(tree){
            freeNode(tree->root);
            free(tree);
        }
        if(solT){
            freeNode(solT->root);
            free(solT);
        }
        CU_FAIL(_("Internal error while allocating memory"));
        //TODO return ??? Or CU_FAIL is enough ?
    }
    
    //sol
    node_t* cat = solT->root;
    node_t* deer = cat->right;
    node_t* creature = deer->left;
    solT->root = creature;
    creature->left = cat->left;
    creature->right = cat->right;
    free(cat->enWord); free(cat->frWord); free(cat);
    deer->left = NULL;
    
    
    char* catStr = "cat";
    
    monitored.malloc = true;
    monitored.free = true;
    SANDBOX_BEGIN;
    delete(tree, catStr);
    SANDBOX_END;
    
    int nbMalloc = stats.malloc.called;
    int nbFree = stats.free.called;
    
    
    //TODO : you sould use free 3 times or wrong number of free's ?
    CU_ASSERT_EQUAL(nbFree,3);
    if(nbFree != 3){
        push_info_msg(_("You should use free 3 times"));
    }
    
    CU_ASSERT_EQUAL(nbMalloc,0);
    if(nbMalloc != 0){
        push_info_msg(_("Why are you using malloc ?"));
    }
    
    int sameT = sameTrees(solT,tree);
    CU_ASSERT_EQUAL(sameT,true);
    if(!sameT)
        push_info_msg(_("Your tree isn't what was expected"));
}

void test_delete_two_children_tree4(){
    set_test_metadata("delete", _("Test deleting a simple node (which has 2 children) using the algorithm explained above. The node's right subtree's leftmost child is node->right"),1);
    //student arguments
    bt_t* tree = tree4();
    bt_t* solT = tree4();
    
    if(!tree || !solT){
        if(tree){
            freeNode(tree->root);
            free(tree);
        }
        if(solT){
            freeNode(solT->root);
            free(solT);
        }
        CU_FAIL(_("Internal error while allocating memory"));
        //TODO return ??? Or CU_FAIL is enough ?
    }
    
    //sol
    node_t* cat = solT->root;
    node_t* deer = cat->right;
    node_t* elephant = deer->right;
    cat->right = elephant;
    elephant->left = deer->left;
    free(deer->enWord); free(deer->frWord); free(deer);
    //sol built
    
    char* deerStr = "deer";
    
    monitored.malloc = true;
    monitored.free = true;
    SANDBOX_BEGIN;
    delete(tree, deerStr);
    SANDBOX_END;
    
    int nbMalloc = stats.malloc.called;
    int nbFree = stats.free.called;
    
    
    //TODO : you sould use free 3 times or wrong number of free's ?
    CU_ASSERT_EQUAL(nbFree,3);
    if(nbFree != 3){
        push_info_msg(_("You should use free 3 times"));
    }
    
    CU_ASSERT_EQUAL(nbMalloc,0);
    if(nbMalloc != 0){
        push_info_msg(_("Why are you using malloc ?"));
    }
    
    int sameT = sameTrees(solT,tree);
    CU_ASSERT_EQUAL(sameT,true);
    if(!sameT)
        push_info_msg(_("Your tree isn't what was expected"));
}


int main(int argc,char** argv)
{
    BAN_FUNCS(strdut,calloc,mmap);
    RUN(test_insert_normal, test_insert_normal_first_malloc_fails, test_insert_normal_second_malloc_fails, test_insert_normal_third_malloc_fails, test_insert_empty_tree, test_insert_already_inserted, test_delete_no_child, test_delete_one_child, test_delete_node_not_found, test_delete_root_replace_null, test_delete_root_replace_node, test_delete_empty_tree, test_delete_two_children_tree1, test_delete_two_children_tree1_root, test_delete_two_children_tree4);
}

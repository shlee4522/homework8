/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */
//second

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node* left;
    struct node* right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);      /* recursive inorder traversal */
void preorderTraversal(Node* ptr);     /* recursive preorder traversal */
void postorderTraversal(Node* ptr);    /* recursive postorder traversal */
int insert(Node* head, int key);       /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);/* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);/* search the node for the key */
Node* searchIterative(Node* head, int key);/* search the node for the key */
int freeBST(Node* head);               /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main()
{
    printf("[----- [LeeSeungHun] [2023041045] -----]");
    char command;
    int key;
    Node* head = NULL;
    Node* ptr = NULL;    /* temp */

    do {
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                   Binary Search Tree #1                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize BST       = z                                       \n");
        printf(" Insert Node          = n      Delete Node                  = d \n");
        printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
        printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
        printf(" Postorder Traversal  = t      Quit                         = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'z': case 'Z':
            initializeBST(&head);
            break;
        case 'q': case 'Q':
            freeBST(head);
            break;
        case 'n': case 'N':
            printf("Your Key = ");
            scanf("%d", &key);
            insert(head, key);
            break;
        case 'd': case 'D':
            printf("Your Key = ");
            scanf("%d", &key);
            deleteLeafNode(head, key);
            break;
        case 'f': case 'F':
            printf("Your Key = ");
            scanf("%d", &key);
            ptr = searchIterative(head, key);
            if (ptr != NULL)
                printf("\n node [%d] found at %p\n", ptr->key, ptr);
            else
                printf("\n Cannot find the node [%d]\n", key);
            break;
        case 's': case 'S':
            printf("Your Key = ");
            scanf("%d", &key);
            ptr = searchRecursive(head->left, key);
            if (ptr != NULL)
                printf("\n node [%d] found at %p\n", ptr->key, ptr);
            else
                printf("\n Cannot find the node [%d]\n", key);
            break;

        case 'i': case 'I':
            inorderTraversal(head->left);
            break;
        case 'p': case 'P':
            preorderTraversal(head->left);
            break;
        case 't': case 'T':
            postorderTraversal(head->left);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

int initializeBST(Node** h) {
    //트리가 비어 있지 않다면, 트리에 할당된 모든 메모리를 해제
    if (*h != NULL)
        freeBST(*h);

    //헤드 노드 생성
    *h = (Node*)malloc(sizeof(Node));
    (*h)->left = NULL; //루트 노드 
    (*h)->right = *h;
    (*h)->key = -9999;
    return 1;
}

void inorderTraversal(Node* ptr)
{
    if (ptr) {
        //왼쪽 -> 루트 -> 오른쪽 순서로 중위순회
        inorderTraversal(ptr->left);
        printf(" %d", ptr->key);
        inorderTraversal(ptr->right);
    }
}

void preorderTraversal(Node* ptr)
{
    if (ptr) {
        //루트 -> 왼쪽 -> 오른쪽 순서로 전위 순회
        printf(" %d", ptr->key);
        preorderTraversal(ptr->left);
        preorderTraversal(ptr->right);
    }
}

void postorderTraversal(Node* ptr)
{
    if (ptr) {
        //왼쪽 -> 오른쪽 -> 루트 순서로 후위순회
        postorderTraversal(ptr->left);
        postorderTraversal(ptr->right);
        printf(" %d", ptr->key);
    }
}

int insert(Node* head, int key)
{
    //새 노드 생성 및 초기화
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;

    //트리가 비었다면, 새 노드를 루트로 설정
    if (head->left == NULL) {
        head->left = newNode;
        return 1;
    }

    //루트 노드에서 시작하여 삽입 위치를 찾음
    Node* parent = head->left;
    Node* current = head->left;

    while (current != NULL) {
        //삽입이 현재 노드보다 작을때
        if (key < current->key) {
            parent = current; //현재 노드를 부모로 설정
            current = current->left; //왼쪽 자식으로 이동
            //삽입이 현재 노드보다 클때
        }
        else if (key > current->key) {
            parent = current; //현재 노드를 부모로 설정
            current = current->right; //오른쪽 자식으로 이동
            //삽입이 이미 존재할때
        }
        else {
            printf("[%d] already exists\n", key);
            free(newNode); //새 노드 메모리 해제
            return 0; //삽입 실패
        }
    }

    //삽입할 위치가 부모 노드의 왼쪽인지 오른쪽인지 결정하여 삽입
    if (key < parent->key) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
    return 1;
}


int deleteLeafNode(Node* head, int key)
{
    //트리가 비어있거나 루트 노드가 없는 경우
    if (head == NULL || head->left == NULL) {
        printf("The tree is empty\n");
        return 0;
    }

    Node* parent = NULL;
    Node* current = head->left;

    // 노드를 찾아 삭제
    while (current != NULL) {
        if (key == current->key) {
            //현재 노드가 리프 노드인 경우
            if (current->left == NULL && current->right == NULL) {
                //부모 노드가 없는 경우
                if (parent == NULL) {
                    head->left = NULL; //루트 노드를 NULL로 설정
                }
                else if (parent->left == current) {
                    parent->left = NULL; //부모의 왼쪽 자식을 NULL로 설정
                }
                else {
                    parent->right = NULL; //부모의 오른쪽 자식을 NULL로 설정
                }
                free(current);
                return 1;
            }
            else {
                //현재 노드가 리프 노드가 아닌 경우
                printf("[%d] is not a leaf node\n", key);
                return 0;
            }
        }
        parent = current; //부모 노드를 현재 노드로 업데이트
        //비교하여 왼쪽 또는 오른쪽 자식으로 이동
        if (key < current->key) {
            current = current->left; //왼쪽 자식으로 이동
        }
        else {
            current = current->right; //오른쪽 자식으로 이동
        }
    }

    //삭제할 노드를 찾지 못한 경우
    printf("Cannot find [%d]\n", key);
    return 0;
}


Node* searchRecursive(Node* ptr, int key)
{
    //현재 노드가 NULL이거나, 현재 노드의 키가 찾는 키와 같은 경우
    if (ptr == NULL || ptr->key == key) {
        return ptr; //노드를 찾았거나 트리의 끝에 도달했을 때 현재 노드 반환
    }

    //찾는게 현재 노드보다 작은 경우
    if (key < ptr->key) {
        return searchRecursive(ptr->left, key); //왼쪽 자식에서 검색 계속
    }
    else {
        return searchRecursive(ptr->right, key); //찾는게 현재 노드보다 큰 경우, 오른쪽 자식에서 검색 계속
    }
}


Node* searchIterative(Node* head, int key)
{
    Node* current = head->left; //루트 노드에서 시작

    while (current != NULL) {
        //현재 노드가 찾는것과 같은 경우
        if (key == current->key) {
            return current; //현재 노드 반환
        }

        //찾는게 현재 노드보다 작은 경우
        if (key < current->key) {
            current = current->left; //왼쪽 자식으로 이동
        }
        else {
            current = current->right; //찾는게 현재 노드보다 큰 경우, 오른쪽 자식으로 이동
        }
    }

    return NULL; //찾는 노드가 없는 경우 NULL 반환
}


int freeBST(Node* head)
{
    // 트리에 할당된 모든 메모리를 해제
    if (head == NULL) {
        return 1;
    }

    if (head->left != head) {
        freeBST(head->left);
    }
    free(head);
    return 1;
}







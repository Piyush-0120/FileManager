#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <direct.h>
#include <dirent.h>
#include <sys/stat.h>

struct node
{
    int isfile;
    char data[100];
    struct node * firstChild;
    struct node * nextSibling;
    struct node * next;
    int  hasChild, exists;
};
typedef struct node node;

/*--------file manager & vdrive--------*/
node *root;
node *currentnode;
node* add_node(char *, int);
node* add_child(node *, char *, int);
node* add_sibling(node *, char *, int);
void displayTree(node *, int);
void removeNode(node *, char *);
void delete(node *);
char* addBefore(char*, char*);
void showdir(node *);
char element[100];

node * add_node(char * data, int markfile)
{
    node *temp = (node*)malloc(sizeof(node));

    if ( temp )
    {
        temp->nextSibling = NULL;
        temp->firstChild = NULL;
        temp->next = NULL;
        strcpy(temp->data, data);
        temp->isfile = markfile;
        temp->hasChild = 0;
        temp->exists = 0;
    }

    return temp;
}

node * add_child(node *n, char * data, int markfile)
{
    node *temp;
    if (n == NULL)
        return NULL;
    temp = add_node(data, markfile);
    n->firstChild = temp;
    return (n = n->firstChild);

}

node * add_sibling(node *n, char * data, int markfile)
{
    /*refer using first child*/
    node *temp;
    if (n == NULL)
        return NULL;
    temp = add_node(data, markfile);
    n->nextSibling = temp;
    return (n = n->nextSibling);
}

void displayTree(node * current, int depth)
{
    int i;
    node *j;
    if (current != NULL)
    {
        current = current->firstChild;
        if (current != NULL)
        {
            j = current;
            while (j != NULL)
            {
                for (i = 0; i < depth; i++)
                    printf("\t");
                printf(" %s\n", j->data);
                displayTree(j, depth + 1);
                j = j->nextSibling;
            }
        }
    }
    return;
}

void showDir(node * current)
{
    if (current->firstChild)
    {
        current = current->firstChild;
        printf("%s\n", current->data);
        while (current->nextSibling)
        {
            current = current->nextSibling;
            printf("%s\n", current->data);
        }
    }
    else
        printf("This directory is empty..\n");
    return;

}

int isChildPresent(node * current, char *childname)
{
    if (current->firstChild)
    {
        if (strcmp(current->firstChild->data, childname) == 0)
        {
            currentnode = current->firstChild;
            return (currentnode->isfile);
        }
        else
        {
            current = current->firstChild;
            while (current->nextSibling)
            {
                if (strcmp(current->nextSibling->data, childname) == 0)
                {
                    currentnode = current->nextSibling;
                    return (currentnode->isfile);
                    /*1: isfile; 0: not isfile; -1:child not present */
                }
                else
                    current = current->nextSibling;
            }
        }
    }
    return -1;
}

struct StackNode
{
    struct node * nodes;
    struct StackNode *snodenext;
};
typedef struct StackNode StackNode;

StackNode* pushNode(StackNode* head, node * n)
{
    StackNode* temp = (struct StackNode*)malloc(sizeof(StackNode));
    if (temp == NULL)
    {
        exit(0);
    }
    temp->nodes = n;
    temp->snodenext = head;
    head = temp;
    return head;
}

StackNode* popNode(StackNode* head)
{
    StackNode* temp = head;
    head = head-> snodenext;
    free(temp);
    return head;
}

struct Stack
{
    char sdata[100];
    struct Stack *snext;
};
typedef struct Stack Stack;

Stack* push(Stack* head, char x[])
{
    Stack* temp = (struct Stack*)malloc(sizeof(Stack));
    if (temp == NULL)
    {
        exit(0);
    }
    strcpy(temp->sdata, x);
    temp->snext = head;
    head = temp;
    return head;
}

Stack* pop(Stack* head, char element[])
{
    Stack* temp = head;
    strcpy(element, head->sdata);
    head = head-> snext;
    free(temp);
    return head;
}
int empty(Stack* head)
{
    return head == NULL ? 1 : 0;
}

void sdisplay(Stack* head)
{
    char str[PATH_MAX] = "";
    Stack *current;
    current = head;
    if (current != NULL)
    {
        while (current != NULL)
        {
            strcpy(str, addBefore(str, current->sdata));
            current = current->snext;
        }

        printf("%s", str);
    }
    else
    {
        printf("The Stack is empty\n");
    }

}

char* addBefore(char* s1, char* s2)
{
    char *s3 = malloc(PATH_MAX);
    int i, j;
    j = 0;
    for (i = 0; s2[i] != '\0'; i++)
    {
        s3[i] = s2[i];
    }
    while (s1[j] != '\0')
    {
        s3[i] = s1[j];
        j = j + 1;
        i = i + 1;
    }
    s3[i] = '\0';
    return s3;

}

void removeNode(node *current, char *nodeName)
{
    node * temp;
    if (isChildPresent(current, nodeName) != -1)
    {
        if (strcmp(current->firstChild->data, nodeName) == 0)
        {

            if (current->firstChild->firstChild != NULL)
                printf("Directory is not empty..\n");
            else {
                temp = current->firstChild;
                current->firstChild = temp->nextSibling;
                free(temp);
                printf("Deleted successfully..\n");
            }
        }
        else
        {
            current = current->firstChild;
            while (current != NULL)
            {
                if (strcmp(current->nextSibling->data, nodeName) == 0)
                {
                    if (current->nextSibling->firstChild != NULL)
                    {printf("Directory is not empty..\n"); break;}
                    else
                    {delete(current); printf("Deleted successfully..\n"); break;}
                }
                current = current->nextSibling;
            }
        }
    }
    else
        printf("%s does not exist..\n", nodeName);
}

void delete(node *before_del)
{
    node *temp;
    temp = before_del->nextSibling;
    before_del->nextSibling = temp->nextSibling;
    free(temp);
}

void createDumpFolder()
{
    struct stat st;
    char *dirName = "that.dumps";
    if (stat(dirName, &st) == -1)
    {
        if (mkdir(dirName) != -1)
        {
            printf("Created %s successfully.\n", dirName);

        }
        else
        {
            perror("mkdir: ");
            printf("Please check whether '%s' file exists.\n", dirName);
        }
    }
}

/*---------------------Virtal Drive-------------------------*/

void vDrive(struct node *n)
{
    char ch[100];
    char ch1[100];
    struct Stack* head = NULL;
    struct StackNode* headNode = NULL;

    printf("\n+----------------------THE VIRTUAL DRIVE--------------------------+\n");
    printf("|   Commands for virtual drive:-                                  |\n");
    printf("|   cd      : Change directory                                    |\n");
    printf("|   cd ..   : Previous directory                                  |\n");
    printf("|   mkdir   : Make directory                                      |\n");
    printf("|   mkfile  : Make new file                                       |\n");
    printf("|   open    : Open a file in a directory                          |\n");
    printf("|   remove  : Remove a file or a folder                           |\n");
    printf("|   ls -a   : Display a directory's files and subdirectories      |\n");
    printf("|   ls -all : Display tree of folders of virtual drive            |\n");
    printf("|   quit -v : quit                                                |\n");
    printf("+-----------------------------------------------------------------+\n\n");
    strcpy(element, "V:\\");
    head = push(head, element);
    strcpy(element, ">");
    head = push(head, element);
    sdisplay(head);
    currentnode = n; /*n = root*/
    headNode = pushNode(headNode, currentnode);
    while (1)
    {

        scanf("%s %s", ch, ch1);
        if (strcmp(ch, "cd") == 0 && strcmp(ch1, "..") != 0)
        {
            currentnode = headNode->nodes;
            if (isChildPresent(currentnode, ch1) == 0)
            {
                head = pop(head, element);

                strcpy(element, ch1);
                head = push(head, element);

                strcpy(element, "\\");
                head = push(head, element);

                strcpy(element, ">");
                head = push(head, element);
                sdisplay(head);
                headNode = pushNode(headNode, currentnode);
                currentnode = headNode->nodes;
            }
            else
            {   printf("No such directory present\n");
                sdisplay(head);
                currentnode = headNode->nodes;
            }
        }
        else if (strcmp(ch, "cd") == 0 && strcmp(ch1, "..") == 0)
        {
            head = pop(head, element);
            head = pop(head, element);
            head = pop(head, element);


            strcpy(element, ">");
            head = push(head, element);
            sdisplay(head);
            headNode = popNode(headNode);
            currentnode = headNode->nodes;

        }
        else if (strcmp(ch, "ls") == 0 && strcmp(ch1, "-a") == 0)
        {
            currentnode = headNode->nodes;
            printf("\nDirectory of ");
            sdisplay(head);
            printf("\n");
            showDir(currentnode);
            printf("\n");
            sdisplay(head);
        }
        else if (strcmp(ch, "ls") == 0 && strcmp(ch1, "-all") == 0)
        {
            printf("\nFolder listing for drive V:\n");
            displayTree(root, 0);
            printf("\n");
            sdisplay(head);
        }
        else if (strcmp(ch, "mkdir") == 0 && strcmp(ch1, "`") != 0)
        {

            if (currentnode->firstChild == NULL)
            {
                currentnode = add_child(currentnode, ch1, 0);
                /*0 represents not a file*/
                /*curent node changed so need to
                point the currentnode to parent*/
                currentnode = headNode->nodes;
                currentnode->hasChild = 1;
                printf("Folder successfully created..\n");

            }
            else if (isChildPresent(currentnode, ch1) == -1)
            {
                currentnode = currentnode->firstChild;
                while (currentnode->nextSibling)
                {
                    currentnode = currentnode->nextSibling;
                }
                currentnode = add_sibling(currentnode, ch1, 0);
                currentnode = headNode->nodes;
                printf("Folder successfully created..\n");
            }

            else {
                currentnode = headNode->nodes;
                printf("Folder name with %s already exists\n", ch1);
            }
            sdisplay(head);
        }

        else if (strcmp(ch, "mkfile") == 0 && strcmp(ch1, "`") != 0)
        {
            FILE *fp;
            char *prefix = "that.dumps";
            char cmd[PATH_MAX] = "notepad ";
            char filePath[PATH_MAX];
            if (currentnode->firstChild == NULL)
            {
                currentnode = add_child(currentnode, ch1, 1);
                currentnode = headNode->nodes;

                snprintf(filePath, PATH_MAX + 1, "%s/%s", prefix, ch1);
                fp = fopen(filePath, "w+");
                fclose(fp);
                strcat(cmd, filePath);
                system(cmd);
                printf("File successfully created..\n");

            }
            else if (isChildPresent(currentnode, ch1) == -1)
            {
                /*isChildPresent(currentnode,ch1)==-1 represents if no such
                named file exists*/
                currentnode = currentnode->firstChild;
                while (currentnode->nextSibling)
                {
                    currentnode = currentnode->nextSibling;
                }
                currentnode = add_sibling(currentnode, ch1, 1);
                currentnode = headNode->nodes;

                snprintf(filePath, PATH_MAX + 1, "%s/%s", prefix, ch1);
                fp = fopen(filePath, "w+");
                fclose(fp);
                strcat(cmd, filePath);
                system(cmd);
                printf("File successfully created..\n");
            }

            else {
                currentnode = headNode->nodes;
                printf("File name with %s already exists\n", ch1);
            }
            sdisplay(head);
        }
        else if (strcmp(ch, "open") == 0 && strcmp(ch1, "`") != 0)
        {
            char *prefix = "that.dumps";
            char cmd[PATH_MAX] = "notepad ";
            char filePath[PATH_MAX];
            if (strcmp(ch1, currentnode->firstChild->data) == 0)
            {
                snprintf(filePath, PATH_MAX, "%s/%s", prefix, ch1);
                strcat(cmd, filePath);
                system(cmd);
            }
            else if (isChildPresent(currentnode, ch1) == 1)
            {
                snprintf(filePath, PATH_MAX, "%s/%s", prefix, ch1);
                strcat(cmd, filePath);
                system(cmd);
            }
            else
            {
                printf("Filename with %s does not exist\n", ch1);
            }
            currentnode = headNode->nodes;
            sdisplay(head);
        }
        else if (strcmp(ch, "remove") == 0 && strcmp(ch1, "`") != 0)
        {
            removeNode(currentnode, ch1);
            currentnode = headNode->nodes;
            sdisplay(head);
        }
        else if (strcmp(ch, "quit") == 0 && strcmp(ch1, "-v") == 0)
        {
            DIR *d;
            char buff[FILENAME_MAX];
            struct dirent *dir;
            d = opendir("./that.dumps");
            _getcwd( buff, FILENAME_MAX );
            if (d)
            {
                while ((dir = readdir(d)) != NULL)
                {
                    char *fullpath, *prefix = "/that.dumps/", *suffix = dir->d_name;
                    if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) continue;
                    snprintf(fullpath, PATH_MAX, "%s/%s/%s", buff, prefix, suffix);
                    if (remove(fullpath) == 0)
                    {

                        continue;
                    }
                    else
                    {
                        printf("%s is not deleted.\n", dir->d_name);
                    }

                }
                closedir(d);
            }

            printf("Files deleted successfully.\n");
            break;
        }
        else
        {
            printf("Not regocnized as a command\n");
            sdisplay(head);
        }
    }
}

/*-------------main--------------------*/

int main(int argc, char *argv[])
{
    int ch;
    node *current;
    createDumpFolder();

    /* The Generic Tree's root */
    root = add_node("root", 0);

    current = root;
    current->hasChild = 1;
    currentnode = root;

    printf("\n+------------------------------------------------------------------+\n");
    printf("|                         W E L C O M E                            |\n");
    printf("+------------------------------------------------------------------+\n");

    while (1)
    {
        printf("\n1       : Enter the Virtual Drive\n");
        printf("2       : Exit\n");
        printf("\nEnter your choice : ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            vDrive(root);
            break;
        case 2:
            exit(1);
        default:
            printf("\nNot regocnized as a command.\n");
        }
    }
}

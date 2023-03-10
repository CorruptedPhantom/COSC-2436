//Linked List Example Again, but with Remove From Beg Function
#include <bits/stdc++.h>
using namespace std;
  
// A linked list node
class Node {
public:
   int data;
   Node* next;
};
  
void push(Node** head_ref, int new_data)
{
   Node* new_node = new Node();
   new_node->data = new_data;
   new_node->next = (*head_ref);
   (*head_ref) = new_node;
}
  
void deleteNode(Node** head_ref, int key)
{
  
   // Store head node
   Node* temp = *head_ref;
   Node* prev = NULL;

   if (temp != NULL && temp->data == key) {
      
     // Changed head
      *head_ref = temp->next;
      
     // free old head
      delete temp;
      return;
   }
   else {
      while (temp != NULL && temp->data != key) {
         prev = temp;
         temp = temp->next;
      }
  
      // If key was not present in linked list
      if (temp == NULL)
         return;
  
      // Unlink the node from linked list
      prev->next = temp->next;
  
      // Free memory
      delete temp;
   }
}

void printList(Node* node)
{
   while (node != NULL) {
      cout << node->data << " ";
      node = node->next;
   }
}
  
// Driver code
int main()
{
  
   // Start with the empty list
   Node* head = NULL;
  
   // Add elements in linked list
   push(&head, 7);
   push(&head, 1);
   push(&head, 3);
   push(&head, 2);
  
   puts("Created Linked List: ");
   printList(head);
  
   deleteNode(&head, 1);
   puts("\nLinked List after Deletion of 1: ");
  
   printList(head);
  
   return 0;
}
//ll.h
// self-referential structure
struct Node {
   int id; // each listNode contains a character
   char name[100];
   struct Node *nextPtr; // pointer to next node
   struct Node *pPtr;//ชี้กลับ
}; // end structure listNode

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*

// prototypes

int deletes( LLPtr *sPtr, int id);
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int id, char name[] );
void printList( LLPtr currentPtr );
void instructions( void );
void printlistR(LLPtr currentPtr);
void clearList(LLPtr *sPtr);


// display program instructions to user
void instructions( void )
{
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert( LLPtr *sPtr, int id, char name[])
{
   LLPtr newPtr; // pointer to new node
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list

   newPtr =(LLPtr) malloc( sizeof( LLnode ) ); // create node

   if ( newPtr != NULL ) { // is space available
      newPtr->id = id; // place value in node
      strcpy(newPtr->name,name);
      newPtr->nextPtr = NULL; // node does not link to another node
      newPtr->pPtr=NULL;
       
      previousPtr = NULL;
      currentPtr = *sPtr;

      // loop to find the correct location in the list
      while ( currentPtr != NULL && id > currentPtr->id ) {
         previousPtr = currentPtr; // walk to ...
         currentPtr = currentPtr->nextPtr; // ... next node
         
      } // end while

      // insert new node at beginning of list
      if ( previousPtr == NULL ) {
         newPtr->nextPtr = *sPtr;
         if(*sPtr)//if(*sPtr!=NULL)
         (*sPtr)->pPtr=newPtr;
         *sPtr = newPtr;
        
      } // end if
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->pPtr=previousPtr;

         newPtr->nextPtr = currentPtr;
         if (currentPtr!=NULL)
         currentPtr->pPtr=newPtr;
 
         
      } // end else
   } // end if
   else {
      printf( "%d not inserted. No memory available.\n", id);
   } // end else
} // end function insert

// delete a list element
int deletes( LLPtr *sPtr, int id )
{
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer

   if(*sPtr == NULL){
      printf("List is empty. Nothing to delete.\n");
      return 0;
   }

   // delete first node
   if ( id == ( *sPtr )->id ) {
      tempPtr = *sPtr; // hold onto node being removed
      *sPtr = ( *sPtr )->nextPtr; // de-thread the node

      if (*sPtr !=NULL) (*sPtr)->pPtr=NULL;
      free( tempPtr ); // free the de-threaded node
      return id;
   } // end if
   ////else {
      previousPtr = *sPtr;
      currentPtr = ( *sPtr )->nextPtr;

      // loop to find the correct location in the list
      while ( currentPtr != NULL && currentPtr->id != id ) {
         previousPtr = currentPtr; // walk to ...
         currentPtr = currentPtr->nextPtr; // ... next node
      } // end while

      // delete node at currentPtr
      if ( currentPtr != NULL ) {
         tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
      if(currentPtr->nextPtr !=NULL)currentPtr->nextPtr->pPtr=previousPtr;
         free( tempPtr );
         return id;
      } // end if
   ////} // end else

   return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( LLPtr currentPtr )
{
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else {
      puts( "The list is:" );

      // while not the end of the list
      while ( currentPtr!= NULL ) {
         printf("%d %s --> ", currentPtr->id,currentPtr->name);
         currentPtr = currentPtr->nextPtr;
      } // end while

      printf( "NULL\n");
       
   } // end else
} // end function printList

void printlistR(LLPtr currentPtr)
{
   if (isEmpty(currentPtr)){
      printf("List is empty\n");
   }
   else{
   while(currentPtr->nextPtr !=NULL){
      currentPtr = currentPtr->nextPtr;
   }
   while(currentPtr != NULL)
   {
      printf("%d %s --> ",currentPtr->id, currentPtr->name);
      currentPtr = currentPtr->pPtr;
   }
   puts("NULL");
}
}

void clearList(LLPtr *sPtr)
{
   LLPtr currentPtr = *sPtr;
   LLPtr temPtr;

   while (currentPtr !=NULL){
      temPtr = currentPtr;
      currentPtr = currentPtr->nextPtr;
      printf( "deleted %d\n", temPtr->id);
      free(temPtr);
   }

   *sPtr = NULL;
}
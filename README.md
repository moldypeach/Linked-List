Linked-List
===========

Linked List

complete exercises 20.1:

  Implement remove( T element )

Use the code you find in Listing 20.2 in the chapter to build a LinkedList class. Add the code to remove a node based 
on content  (you can use the code to remove a node based on index for ideas).  Use the LinkedList generic class to 
construct a program that will read in the following line of text, parse it into tokens, and store it in the linked list.
You program should then traverse the linked list to print out the parsed sentence. The sentence you will use to 
demonstrate the program is this one (from Edgar Allen Poe’s “Fall of the House of Usher”):

  DURING the whole of a dull, dark, and soundless day in the autumn of the year, when the clouds hung oppressively low 
  in the heavens, I had been passing alone, on horseback, through a singularly dreary tract of country; and at length 
  found myself, as the shades of the evening drew on, within view of the melancholy House of Usher.
  
The sentence has been chosen to be long and to have a variety of punctuation and capitalization to test against. 
Punctuation should not result in a change in token – so “on” and “on,” should result in the same token. Once you have
the program creating the list, you will complete exercise 20.1 by deleting all references to the word “of” from the list.  

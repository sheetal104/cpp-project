#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<process.h>
#include<ctype.h>

//Functions for Hangman
const int MAXLENGTH=80;
const int MAX_TRIES=5;

int Fill(char, char[], char[]);
void Unknown(char[], char[]);

//Functions for Hand Cricket
char toss();
int first_innings (char batsman);
void end_innings (char &batsman);
int second_innings (char batsman, int target);
void display_winner (char current_batsman, int runs_scored, int runs_chased);

void main()
{
clrscr();
int choice;
cout<<"*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n";
cout<<"\n\t\t\t\tGAME ZONE\n\n\n";
cout<<"*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n";
//cout<<"\n\n      **************Project by S**************\n\n";
cout<<"\n\n\n\n  This project allows you to play a game of your choice.";
cout<<"\n\n   GAME MENU\n   =========\t\n\n  1.HANGMAN\n  2.HAND CRICKET\n\n";
cout<<"\n   Enter your choice of game:\t";
cin>>choice;
clrscr();

 if(choice==1)
 { char unknown [MAXLENGTH];
   char letter;
   int wrong_guesses=0;
   char word[MAXLENGTH];
   char list[][MAXLENGTH] = { "FROZEN","INCEPTION",
			       "SPECTRE","AVATAR",
			       "RATATOUILLE","MALEFICENT",
			       "INTERSTELLAR","TITANIC",
			       "CROODS","GODZILLA"         };

   //choose and copy a word from array of words randomly
   randomize();
   int n=random(10);
   strcpy(word,list[n]);

   // Initialize the secret word with the * character.
   Unknown(word, unknown);
   // welcome the user
   cout<<"\n\t\t\t\t HANGMAN \n";
   cout<<"\n===============================================================================\n";
   cout<<"\n\n\tGuess a Movie Name.";
   cout << "\n\n\tEach letter is represented by a star.";
   cout << "\n\n\tYou have to type only one letter in one try.";
   cout << "\n\n\tYou have " << MAX_TRIES << " tries to try and guess the word.";
   cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

   // Loop until the guesses are used up
   while (wrong_guesses < MAX_TRIES)
     {  cout << "\n\n" << unknown;
	cout << "\n\nGuess a letter(A-Z): ";
	cin >> letter;
	// Fill secret word with letter if the guess is correct,
	// otherwise increment the number of wrong guesses.
	if(Fill(letter, word, unknown)==0)
	  {
	     cout << endl << "Oops,that letter isn't in there!" << endl;
	     wrong_guesses++;
	  }
	else
	  {
	     cout << endl << "Good job, you found a letter!" << endl;
	  }
	// Tell user how many guesses has left.
	cout << "You have " << MAX_TRIES - wrong_guesses;
	cout << " guesses left." << endl;
	// Check if they guessed the word.
	if(strcmp(word, unknown) == 0)
	 {
	    cout <<"\n"<<word<< endl;
	    cout << "\n\nCongrats! You got it!";
	    break;
	 }
     }
     if(wrong_guesses == MAX_TRIES)
      {
	cout << "\nSorry, you lose...you've been hanged." << endl;
	cout << "The word was :  " << word << endl;
      }
 }

 else if(choice==2)
  { //Hand Cricket
    randomize();
    clrscr();
    cout<<"\n\n\t\t\t       HAND CRICKET\n";
    cout<<"\n===============================================================================\n" ;
    cout << "\n  INSTRUCTIONS\n\n";
    cout <<"* Player refers to the human player, and AI refers to the CPU.\n\n";
    cout << "* For the toss, both the players select from 'odd' and 'even' and make throws; "
	 << "  if the sum of these is odd/even, then the side having chosen that will bat     first.\n\n";
    cout << "* For the play, the batsman and the bowler make throws at every ball; if the    throws are the same, "
	 << " the batsman is out, else the throw gets added to the        batsman's runs.";
    char batsman = toss();
    if (batsman == 'a')
   {    // a for AI, p for Player
    cout << "AI wins the toss and thus will bat first" << endl;
   }
    else
   { cout << "Player wins the toss and thus will bat first" << endl;
   }
   getch();
   int runs_scored = first_innings(batsman);
   end_innings(batsman);
   int runs_chased = second_innings(batsman, runs_scored+1);
   display_winner(batsman, runs_scored, runs_chased);
 }

 else
 cout<<"Enter a valid choice!";
getch();
}


/* Take a one character guess and the secret word, and fill in the
 unfinished guessword. Returns number of characters matched.
 Also, returns zero if the character is already guessed. */

int Fill (char guess, char secretword[], char guessword[])
{
  int i;
  int matches=0;
  for (i = 0; secretword[i]!='\0'; i++)
   {
    // Did we already match this letter in a previous guess?
    if (guess == guessword[i])
    return 0;
    // Is the guess in the secret word?
    if (guess == secretword[i])
     {
     guessword[i] = guess;
     matches++;
     }
   }
   return matches;
}


// Initialize the unknown word
void Unknown (char word[], char unknown[])
{
  int i;
  int length = strlen(word);
  for (i = 0; i < length; i++)
  unknown[i]='*';
  unknown[i]='\0';
}

char toss()
 { cout << "\n\n\n*=*=TOSS*=*=\n\n";
   char ch;
   cout << endl << "Please select your option for the toss (o)dd/(e)ven: ";
   cin >> ch;
   int p_gesture, a_gesture, sum;
   cout << endl << "Enter your throw/gesture (from 1-6): ";
   cin >> p_gesture;
   a_gesture = random(6) + 1;
   cout << endl << "AI plays: " << a_gesture;
   getch();
   sum = a_gesture + p_gesture;
   cout << "\n\nThe sum is " << sum << endl;
   char batsman;
   // Decide winner of the Toss
  switch (ch)
    {
      case 'o': // Player chose odd
	       if (sum % 2 != 0)
		batsman = 'p';
	       else
		batsman = 'a';
	       break;
     case 'e': // Player chose even
	      if (sum % 2 == 0)
		batsman = 'p';
	      else
		batsman = 'a';
	      break;
    default: cout<<endl<<"ERROR: Unrecognized option. Please enter from o/e.";
   }
    return batsman;
}

int first_innings (char batsman)
  { clrscr();
    cout << "\n\n*=*=FIRST INNINGS*=*=\n\n";
    int score = 0, a_throw, p_throw;
    if (batsman == 'a')
    {
	cout << endl << "CURRENT BATSMAN: AI\n";
    }
    else
    { cout << endl << "CURRENT BATSMAN: Player\n";
    }
    do
    { cout << endl << "Please enter your throw for this turn (1-6): ";
      cin >> p_throw;
      // Error testing
      if (p_throw < 1 || p_throw > 6)
      {
	cout << p_throw << " is not a recognized throw.";
	continue;
      }
    a_throw = random(6)+1;
    cout << "AI chose to throw " << a_throw;
    getch();
    if (p_throw != a_throw)
     {
       if (batsman == 'p')
       { score += p_throw;
	 cout << endl << "Player gets " << p_throw << " runs";
       }
       else
       { score += a_throw;
	 cout << "\n\nAI gets " << a_throw << " runs";
       }
       cout << endl << "SCORE: " << score << endl;
       }
       else
       { cout << endl << "******  That's OUT!!  ******";
       }
    } while (p_throw != a_throw);
    cout << endl << "The batsman scored " << score << " runs";
    getch();
    return score;
}

void end_innings (char &batsman)
{
   if (batsman == 'p')
   {
       cout << "\n\nThis ends the first innings. AI is the new batsman";
       batsman = 'a';
   } else
   {
       cout << "\n\nThis ends the first innings. Player is the new batsman";
       batsman = 'p';
   }
   getch();
}

int second_innings (char batsman, int target)
{
    clrscr();
    cout << "\n\n*=*=SECOND INNINGS*=*=\n\n";
    int score=0,a_throw, p_throw;
    if (batsman == 'a')
    { cout << endl << "CURRENT BATSMAN: AI\n";
    }
    else
    { cout << endl << "CURRENT BATSMAN: Player\n";
    }
    cout << "\nTARGET: " << target << endl;
    do {
	cout << endl << "Please enter your throw for this turn (1-6): ";
	cin >> p_throw;
	// Error testing
	if (p_throw < 1 || p_throw > 6) {
	    cout << p_throw << " is not a recognized throw.";
	    continue;
	}
	a_throw = random(6)+ 1;
	cout << "AI chose to throw " << a_throw;
	getch();
	if (p_throw != a_throw)
	 { if (batsman == 'p')
	    {
		score += p_throw;
		cout << endl << "Player gets " << p_throw << " runs";
	    }
	    else
	    { score += a_throw;
	      cout << "\n\nAI gets " << a_throw << " runs";
	    }
	    cout << endl << "SCORE: " << score << endl;
	    if (score<target)
		cout << (target - score) << " runs to win\n";
	}
	else
	{
	    cout << endl << "******  That's OUT!!  ******";
	}
    } while ( (p_throw != a_throw) && (score < target) );
    cout << endl << "The batsman scored " << score << " runs";
    getch();
    return score;
}

void display_winner (char current_batsman, int runs_scored, int runs_chased) {
    if (current_batsman == 'p')
    {
	if (runs_chased > runs_scored)
	    cout << "\n\n****** Congrats Player! You won the match! ******";
	else
	    cout << "\n\n****** Player, you lost the match! ******";
    } else
    {
	if (runs_chased > runs_scored)
	    cout << "\n\n****** Player, you lost the match! ******";
	else
	    cout << "\n\n****** Congrats Player! You won the match by " << runs_scored - runs_chased << " runs! ******";
    }
    getch();
}



/* rmcmt.c Mark Dolan, CIS 2107, Comment Remover 091614 */

#include <stdio.h>
/*
The variables INSIDE_COMMENT, POSS_INSIDE, POSS_OUTSIDE are specific to COMMENT PARSING
The variable INSIDE_QUOTE is specific to QUOTE parsing
The variable OUT applies to BOTH QUOTES AND COMMENTS
*/
#define OUT 0
#define INSIDE_COMMENT 1
#define POSS_INSIDE 2
#define POSS_OUTSIDE 3
#define INSIDE_QUOTE 4

int main(int argc, char **argv) {
	int state=OUT;
	int cur;
	int temp;
	int lines = 0;
	int lineError = 0;

while ((cur=getchar())!=EOF) // beginning of main loop from beginning of file to end of file
{

	/* STATE LOGIC: OUT */

	if (state == OUT && cur=='/') //if the state is outside of a comment and encounters a slash, this *might* be the beginning of a comment
	{
		state = POSS_INSIDE;
		temp = cur;
	}
	else if (state == OUT && cur =='\"' || cur == '\'') // if parsing outside of a comment and coming across a quote (single OR double) then write the character...
	{
		putchar(cur);
		state = INSIDE_QUOTE; //and set the state to INSIDE_QUOTE
		lineError = lines; //record line number in case the quote never closes
	}
	else if(state == OUT) //if after the previous checks, the parser is still outside of a comment, write the character
	{
		putchar(cur);
	}

	/* STATE LOGIC: POSS_INSIDE */

	else if(state == POSS_INSIDE && cur == '*') //if the program has detected a potential beginning of a comment (a slash) and the following character is a '*'...
	{
		state = INSIDE_COMMENT; //then you are inside a comment
		lineError = lines; //and should record the line number in case it doesn't close
	}
	else if(state == POSS_INSIDE && cur=='\"' || cur=='\'') //if the program has detected a possible beginning of comment but the current character is a " or '...
	{
		putchar(temp); //write the last character
		putchar(cur); //as well as the current character
		state = IN_QUOTE; //and set the state to inside quote.
		lineError = lines; //record line number in case of error
	}
	else if(state == POSS_INSIDE) //if there is a possible comment beginning but it ends up not being a comment (the if/else clauses above would have determined that already)
	{
		putchar(temp); //then write the last character
		putchar(cur); //as well as the current one
		state = OUT; //set the state to OUT
	}

	/* STATE LOGIC: INSIDE_COMMENT */

	else if(state == INSIDE_COMMENT && cur == '*'){ //if the state is INSIDE_COMMENT and it encounters a '*'
		state = MAYBE_OUT; //then it is potentially the ending of a comment
		lineError = lines; //record the line error
	}
	else if(state == INSIDE_COMMENT)
  {
		// do nothing (this is where the comments are filtered out)
	}

	/* STATE LOGIC: MAYBE_OUT */

	else if(state == MAYBE_OUT && cur=='/') //if the processor comes upon a * (setting to MAYBE_OUT) then a /
	{
		state = OUT; //then that is the end of the comment
	}
	else if(state == MAYBE_OUT) //if the processor comes upon a * (settings it to MAYBE_OUT) but the above statement is not executed...
	{
		state = INSIDE_COMMENT; //then it was just a * and not the end of the comment and so the program returns to that state.
	}
	/* STATE LOGIC: IN_QUOTE */
	else if(state == IN_QUOTE && cur=='\"' || cur == '\'')
	{
		putchar(cur); //if inside a quote and encounters a " or '...
		state = OUT; //then set the state to OUT
	}
	else if(state == IN_QUOTE) //
	{
		putchar(cur);
	}

	/* LINE COUNTER */

	if(cur == '\n')
	{
		lines++; // when new line begins, increment line count
	}
}
//end of white loop

/*
If state is INSIDE_COMMENT at the end of the file, the comment was not properly closed.
If state is INSIDE_QUOTE at the end of the file, the quotations were not properly closed.
Otherwise, the program decommented successfully according to how it should have.
*/
if(state == IN)
{
	printf("A comment was not properly closed on line %d\n", lineError);
	return 1; //error
}
else if(state == IN_QUOTE)
{
	printf("No terminating quotation mark found on line %d\n", lineError);
	return 1; //error
}else{
	printf("program decommented successfully\n");
	return 0; //no error
}
}//End Main

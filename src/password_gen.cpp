// 9/5/21 JFS
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "rnd.h"

using namespace std;

// ************************** Parameters *****************************

#define PASSWORD_DEFAULT_LENGTH 16

// ************************** ASCII table *****************************
/*
        0	1	2	3	4	5	6	7	8	9	A	B	C	D	E	F
U+0020		!	"	#	$	%	&	'	(	)	*	+	,	-	.	/
U+0030	0	1	2	3	4	5	6	7	8	9	:	;	<	=	>	?
U+0040	@	A	B	C	D	E	F	G	H	I	J	K	L	M	N	O
U+0050	P	Q	R	S	T	U	V	W	X	Y	Z	[	\	]	^	_
U+0060	`	a	b	c	d	e	f	g	h	i	j	k	l	m	n	o
U+0070	p	q	r	s	t	u	v	w	x	y	z	{	|	}	~	 DEL
*/
// ************************** ASCII Table extended *****************************
// ************************** *****************************

#define DEBUG 0

 // a-z A-Z 2-9
 // sauf oOl1
 // Using ASCII 48-57 + 65-90 + 97-122 + 41 + 43-46
 // Available space before char rejection: 67
 // 67 = 0-61; 8 + 25 + 26, we will reject 1 + 2 chars afterwards + 5 special characters
char get_char() {
  Random_number_generator rnd_gen;
  unsigned int char_space {67};
  int rnd_val {rnd_gen.read_int(char_space - 1)};
  int out_val {0};
  #if DEBUG == 1
    cout << "rnd_val " << rnd_val << flush; // Debug
  #endif
  // Numerical 0-9
  if (rnd_val < 10) {
    out_val = rnd_val + (0x30 - 0); // 0x30; // ASCII 0-9
  }
  // Upper alpha
  else if ((rnd_val >= 10) && (rnd_val < 36)) {
    out_val = rnd_val + (0x41 - 10); // 0x41; // ASCII A-Z
  }
  // Lower case alpha
  else if ((rnd_val >= 36) && (rnd_val < 62)) {
    out_val = rnd_val + (0x61 - 36); // 0x61; // ASCII a-z
  }
  // Special characters
  else if (rnd_val == 62) {
    out_val = 0x21; // 0x21; // !
  }
  else if ((rnd_val >= 63) && (rnd_val < 67)) {
    out_val = rnd_val + (0x23 - 63); // 0x23; // ASCII a-z
  }
  #if DEBUG == 1
    cout << " - out_val " << out_val << endl; // Debug
  #endif
  // Chack rejected chars
  // Rejecting: 0, 1, I, O, i, l, o
  if ((out_val == 0x30) || \
      (out_val == 0x31) || \
      (out_val == 0x49) || \
      (out_val == 0x4f) || \
      (out_val == 0x69) || \
      (out_val == 0x6c) || \
      (out_val == 0x6f))
  {
    #if DEBUG == 1
      cout << "Rejected char, trying again." << endl; // Debug
    #endif
    out_val = get_char();
  }
  /*
  if (out_val == 0x30) out_val += 3; // Reject 0
  else if (out_val == 0x31) out_val += 5; // Reject 1
  else if (out_val == 0x49) out_val++; // Reject I
  else if (out_val == 0x4f) out_val++; // Reject O
  else if (out_val == 0x69) out_val++; // Reject i
  else if (out_val == 0x6c) out_val++; // Reject l
  else if (out_val == 0x6f) out_val++; // Reject o
  */
  //
  return out_val;
}

// ************************** *****************************

int main(int argc, char** argv) {
  cout << "Welcome ... \n" << flush;
  //
  string application_name;
  int num_chars {0}; // Number of whished characters in the password
  // Read from command line
  bool password_lenght_set {0};
  bool application_name_set {0};
  {
    if (argc == 2) {
      string application_name_tmp {argv[1]};
      application_name = application_name_tmp;
      application_name_set = 1;
    }
    if (argc == 3) {
      string application_name_tmp {argv[1]};
      application_name = application_name_tmp;
      // if 'd' set to default
      if (argv[2][0] == 'd') num_chars = PASSWORD_DEFAULT_LENGTH;
      else num_chars = atoi(argv[2]);
      application_name_set = 1;
      password_lenght_set = 1;
    }
  }

  // Set applicatin name if not passed by console parameter

  if (!application_name_set) {
    cout << "Please state application name: " << flush;
    cin >> application_name;
  }

  // Set password lenght if not passed by console parameter

  if (!password_lenght_set) {
    cout << "How many caracters in the password (number or d for default): " << flush;
    string entered_value;
    cin >> entered_value;
    if (entered_value == "d") {
      int password_default_length {PASSWORD_DEFAULT_LENGTH};
      cout << "\nDefault length is " << password_default_length << endl;
      num_chars = password_default_length;
    }
    else {
      num_chars = atoi(entered_value.c_str());
    }
  }

  // Generate password

  string out_password;
  for (int i {0}; i < num_chars; i++) out_password += get_char();

  // Output password and save to file

  cout << "\nHere is a randomly generated password for " << application_name \
       << " (length " << num_chars << "): " << out_password << endl;
  ofstream out_file {"passwords.txt", std::ofstream::out | std::ofstream::app};
  out_file << "Password for " << application_name << " (length: " << num_chars << ") -> " << out_password << endl;
}

  // *******************  *****************

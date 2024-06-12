#include <iostream>
#include <Windows.h>

using namespace std;

// defines the ascii codes
#define ASCII_MINUS 0x2D
#define ASCII_PLUS 0x2B
#define ASCII_ZERO 0x30

// defines a few constant functions
#define VALID(I) (((I >= 0 && I <= 0x9)))
#define TO_INT(I) (((I - 0x30)))

namespace CharTools
{
	// converts a a given lpcstr to a four byte integer
	BOOL ToInt(LPCSTR lpString, PINT pResult)
	{
		// is the number negative
		BOOL Negative;
		// compares the first character to the ascii minus code
		if (lpString[0] == ASCII_MINUS)
		{
			// increments the char pointer by one byte
			lpString++;
			// sets minus to true
			Negative = TRUE;
		}
		else
		{
			// sets minus to false
			Negative = FALSE;
			// compares the first character to the ascii plus code
			if (lpString[0] == ASCII_PLUS)
				// increments the char pointer by one byte
				lpString++;
		}
		// iterates through the characters while the ascii code is zero
		// this gets to the end of the zeros in the string
		while (lpString[0] == ASCII_ZERO)
			// increments the char pointer by one byte
			lpString++;
		// stores the result
		signed long long result = 0;
		// stores an index for the char array
		unsigned int index = 0;
		// converts the ascii code into the integer value it represents
		unsigned int value = TO_INT(lpString[index]);
		// enters a while loop and checks if it's a valid integer value
		while (VALID(value))
		{
			// checks if the counter is not equal to 0xB
			if (index != 0xB)
			{
				// adds the integer value to the result
				result = (result * 0xA) + value;
				// increments the char index
				index++;
				// converts the ascii code into the integer value it represents
				value = TO_INT(lpString[index]);
			}
			else
				// function failed
				return false;
		}
		// checks if the value exceeds the limit of an integer type
		if (result - Negative >= 0x80000000)
			// function failed
			return false;
		// if the input value was negative
		if (Negative)
			// subtracts the value from zero
			result = 0 - result;
		// stores the result in the second argument pointer
		*pResult = result;
		// function succeeded
		return true;
	}
}

// defines the structure passed into the disassembled function
typedef struct _STRUCT_ONE
{
	char padding_0x0[0x63]; // 0x0
	char char_0x63; // 0x63
} STRUCT_ONE, *PSTRUCT_ONE;

// one structure argument
// boolean return type
// validates an attribute of the given struct type?
BOOL ValidateAttribute(PSTRUCT_ONE pStructOne)
{
	// if the first argument exists and checks if a char at offset 0x63 exists
	if (pStructOne && pStructOne->char_0x63 == 0)
		// returns false
		return FALSE;
	// returns true
	return TRUE;
}

// defines the structure passed into the disassembled function
typedef struct _STRUCT_THREE
{
	int int_0x0; // 0x0
	int int_0x4; // 0x4
} STRUCT_THREE, *PSTRUCT_THREE;

// defines the structure passed into the disassembled function
typedef struct _STRUCT_TWO
{
	char padding_0x0[0x8]; // 0x0
	STRUCT_THREE three_0x8; // 0x8
} STRUCT_TWO, *PSTRUCT_TWO;

// two structure arguments
// void return type
VOID InitWithStruct(PSTRUCT_TWO pStructTwo, PSTRUCT_THREE pStructThree)
{
	pStructThree->int_0x0 = pStructTwo->three_0x8.int_0x0;
	pStructThree->int_0x4 = pStructTwo->three_0x8.int_0x4;
}

#define OFFSET(I) (((DWORD)I - 0x8))

// one pointer argument
// boolean return type
DWORD GetValue(PDWORD pAddress)
{
	// checks if the first argument exists
	if (pAddress)
	{
		// returns a dword at a minus offset
		return *(DWORD*)OFFSET(pAddress);
	}
	else
	{
		// function failed
		return NULL;
	}
}

LPCSTR Mystery(DWORD dwValue)
{
	// checks the value
	switch (dwValue)
	{
	case 6: return "E";
	case 7: return "D";
	case 8: return "C";
	case 9: return "B";
	default: return "A";
	}
}

// the main entry point
int ma56756in()
{
	// stores the result
	int result;
	// calls the function
	if (CharTools::ToInt("-877", &result))
	{
		// prints the result
		cout << result << endl;
	}
	// waits to exit
	cin.get();
	return result;
}
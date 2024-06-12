#include <iostream>
#include <Windows.h>

using namespace std;

#define STR_END 0

// defines the structure used in the disassembled function
typedef struct _DWORD_LIST
{
	// contains the length of the data
	int siLength; // 0x0
	// an array of dwords
	int dwArray[]; // 0x4
} DWORD_LIST, *PDWORD_LIST;

// finds an element in a given dword list
__int64 Find(PDWORD_LIST pDwordList, DWORD dwElement)
{
	// checks the size of the dword list
	if (pDwordList->siLength > 0)
		// iterates through the dword array embedded within the structure
		for (int index = 0; index < pDwordList->siLength; index++)
			// checks the value
			if (pDwordList->dwArray[index] == dwElement)
				// returns 1 left shifted by the counter (bitmask)
				return 1 << index;
	// function failed
	return NULL;
}

namespace String
{
	// thumb-2
	// argument is a constant char array pointer
	// dword return type
	DWORD GetLength(LPCSTR pByteArray)
	{
		// validates the byte array pointer
		if (pByteArray)
		{
			// defines a loop counter
			int index = 0;
			// iterates through the byte array
			while (pByteArray[index] != 0)
				// increments the index
				index++;
			// subtracts the array base address from the element address
			// basically it's finding the element offset from the base of the array
			// clears the last 2 bits of the offset with a bitmask
			return (&pByteArray[index] - pByteArray) & 0x3FFFFFFF;
		}
		// function failed
		return NULL;
	}

	// four arguments
	// return type dword
	// compares two ansi strings
	// it's strcmp
	DWORD Compare(LPCSTR lpFirstString, LPCSTR lpSecondString, INT dwLength)
	{
		// iterates through both char arrays
		for (int i = 0; dwLength > 0; i++, dwLength--)
			// checks if it is the end of the string or the two bytes do not match
			if (lpFirstString[i] == STR_END || lpFirstString[i] != lpSecondString[i])
				// subtracts the second byte from the first and returns the result
				return lpFirstString[i] - lpSecondString[i];
		// returns zero (strings match)
		return 0;
	}

	DWORD Compare(LPCSTR lpFirstString, LPCSTR lpSecondString)
	{
		// creates a loop counter
		int i = 0;
		// iterates through both char arrays
		for (; lpFirstString[i] != STR_END && lpFirstString[i] == lpSecondString[i]; i++);
		// subtracts the second byte from the first and returns the result
		return lpFirstString[i] - lpSecondString[i];
	}
}

const char hexTable[] = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

char* URLEncode(char* input, int length)
{
	int nInputLen = length;
	int nOutputLen = nInputLen * 3;

	char* output = (char*)malloc(nOutputLen + 1);
	char* retOutput = output;
	output[nOutputLen] = '\0';

	for (int i = 0; i < nInputLen; i++)
	{
		*output++ = '%';
		*output++ = hexTable[(input[i] & 0xF0) >> 4];
		*output++ = hexTable[(input[i] & 0x0F)];
	}

	return retOutput;
}

typedef struct _WORKER_THREAD
{
	BYTE unk_0x0[0x4];
	DWORD Count; // The amount of workers associated with this worker thread.
	BYTE unk_0x8[0x10];
	LIST_ENTRY Workers; // A linked list of system workers for this worker thread.
	BYTE unk_0x28[0x30];
} WORKER_QUEUE, *PWORKER_QUEUE;

int main()
{
	cout << hex << 0x4 + sizeof(DWORD) + 0x10 + sizeof(LIST_ENTRY) + 0x30 << endl;
	cin.get();
}
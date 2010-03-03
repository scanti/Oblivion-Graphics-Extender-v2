#include "TextBuffer.h"

TextBuffer::TextBuffer(int size)
{
	Buffer = new char[size];
	BufferMaxSize=size;
	BufferUsed=0;
	Overrun=false;
}

TextBuffer::~TextBuffer()
{
	delete [] Buffer;
}

void TextBuffer::ResetBuffer()
{
	Buffer[0]=0;
	BufferUsed=0;
	Overrun=false;
	return;
}

void TextBuffer::ResizeBuffer(int size)
{
	delete [] Buffer;
	Buffer = new char [size];
	BufferMaxSize=size;
	BufferUsed=0;
	return;
}

bool TextBuffer::AddText(char *text)
{
	
	if(!Overrun)
	{
		int len = strlen(text);
		if ((BufferUsed+len)<BufferMaxSize)
		{
			strcpy_s(&Buffer[BufferUsed],BufferMaxSize-BufferUsed,text);
			BufferUsed=BufferUsed+len;
			return false;
		}
		else
			Overrun=true;
	}
	return true;
}

bool TextBuffer::AddFormatedText(char *Format, ...)
{
	va_list		ArgList;

	if (!Overrun)
	{
		va_start(ArgList,Format);
		int len=_vscprintf(Format,ArgList);
		if((BufferUsed+len)<BufferMaxSize)
		{
			vsprintf_s(&Buffer[BufferUsed],BufferMaxSize-BufferUsed,Format,ArgList);
			BufferUsed=BufferUsed+len;
			va_end(ArgList);
			return false;
		}
		va_end(ArgList);
		Overrun=true;
	}
	return true;		
}

bool TextBuffer::AddChar(char text)
{
	if(!Overrun)
	{
		Buffer[BufferUsed]=text;
		BufferUsed++;
		if (BufferUsed>=BufferMaxSize)
		{
			Buffer[BufferMaxSize-1]=0;
			Overrun=true;
			return true;
		}
		return false;
	}
	return(true);
}

bool TextBuffer::NewLine()
{
	return AddText("\n");
}



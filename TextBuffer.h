#pragma once

class TextBuffer
{
public:
	TextBuffer(int size);
	~TextBuffer();

	void ResetBuffer(void);
	void ResizeBuffer(int size);
	bool AddText(char *text);
	bool AddFormatedText(char *Format, ...);
	bool AddChar(char text);
	bool NewLine(void);

	char		*Buffer;

	int			BufferMaxSize;
	int			BufferUsed;
	bool		Overrun;
};


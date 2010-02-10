#pragma once

#include <vector>
#include "shlobj.h"
#include "shlwapi.h"

void SetPrivateProfile(char* section,char *setting, int value, char* filename);
void SetPrivateProfile(char* section,char *setting, char* value, char *filename);
void SetPrivateProfile(char *section, char *setting, bool value, char *filename);
void SetPrivateProfile(char *section, char *setting, float value, char *filename);

void GetPrivateProfile(char* section,char *setting, int &value, char* filename);
void GetPrivateProfile(char* section,char *setting, char* value, char *filename);
void GetPrivateProfile(char *section, char *setting, bool &value, char *filename);
void GetPrivateProfile(char *section, char *setting, float &value, char *filename);

class globalbase
{
protected:
	char* file;
	char* section;
	char* setting;

public:
	static char SettingsPath[260];
	static bool IsPathSet;

	virtual void RegisterOnList()=0;
	virtual void SetINI()=0;
	virtual void GetINI()=0;
};

typedef std::vector<globalbase*> GlobalsType;

class INIList
{
public:
	GlobalsType GlobalsList;

	static INIList *Singleton;

	static INIList* GetSingleton(void);
	void RegisterSetting(globalbase *global);
	void ReadAllFromINI();
	void WriteAllToINI();
};

template <class dataType>
class global:public globalbase
{
public:
	global(dataType initdata, char* initfile, char* initsection, char* initsetting)
	{
		data=initdata;
		if (initfile)
			file=initfile;
		else
			file="OBGE.ini";
		section=initsection;
		setting=initsetting;
		RegisterOnList();
	}

	virtual dataType Get(void)
	{
		return(data);
	}

	virtual void Set(dataType indata)
	{
		data=indata;
	}

	virtual void RegisterOnList(void)
	{
		INIList::GetSingleton()->RegisterSetting(this);
	}

	virtual void SetINI(void)
	{
		char Filepath[260];

		if(!IsPathSet)
		{
			if(FAILED(SHGetFolderPathA(NULL,CSIDL_PERSONAL,NULL,SHGFP_TYPE_CURRENT,SettingsPath)))
			{
				_MESSAGE("BIG FAT JUICY ERROR - Couldn't find My Documents folder");
				_MESSAGE("Using Default settings.");
				strcpy(SettingsPath,"\\data\\ini\\");
			}
			else
			{
				PathAppendA(SettingsPath,"\\My Games\\Oblivion\\");
			}
			IsPathSet=true;
		}
		strcpy(Filepath,SettingsPath);
		PathAppendA(Filepath,file);
		SetPrivateProfile(section,setting,data,Filepath);
	}

	virtual void GetINI(void)
	{
		char Filepath[260];

		if(!IsPathSet)
		{
			if(FAILED(SHGetFolderPathA(NULL,CSIDL_PERSONAL,NULL,SHGFP_TYPE_CURRENT,SettingsPath)))
			{
				_MESSAGE("BIG FAT JUICY ERROR - Couldn't find My Documents folder");
				_MESSAGE("Using Oblivion's folder instead.");
				strcpy(SettingsPath,"\\data\\ini\\");
			}
			else
			{
				PathAppendA(SettingsPath,"\\My Games\\Oblivion\\");
			}
			IsPathSet=true;
		}
		strcpy(Filepath,SettingsPath);
		PathAppendA(Filepath,file);
		GetPrivateProfile(section,setting,data,Filepath);
	}

	dataType data;
};



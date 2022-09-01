/* sample_multithread_c_program.c
 compile with: /c

  Bounce - Creates a new thread each time the letter 'a' is typed.
  Each thread bounces a character of a different color around
  the screen. All threads are terminated when the letter 'Q' is
  entered./**/

#include <windows.h>/**/
#include <stdlib.h>/**/
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>

#define MAX_THREADS  32

/* The function getrandom returns a random number between min and max, which must be in integer range./**/
#define GET_RAND( min, max ) \
            (SHORT)((rand() % (int)(((max) + 1) - (min))) + (min))
#define GET_RAND_DELTA( min, delta ) \
            (SHORT)((rand() % (int)((delta) + 1)) + (min))?/*reminder can't be equal to devisor(Dividend/Devisor=Quotient and Reminder), for this need to use "+ 1"*/

    /* Thread 1: main/**/
int C_WIN32_multithread(const int argc, char* argv[]);
    /* Keyboard input, thread dispatch/**/
void KbdFunc(void);
    /* Threads 2 to n: display/**/
void BounceProc(void* MyID);
    /* Screen clear/**/
void ClearScreen(void);
    /* Program shutdown/**/
void ShutDown(void);
    /* Display title bar information/**/
void WriteTitle(int ThreadNum);

HANDLE  hConsoleOut;                 /* Handle to the console/**/
HANDLE  hRunMutex;                   /* "Keep Running" mutex/**/
HANDLE  hScreenMutex;                /* "Screen update" mutex/**/
int     ThreadNr;                    /* Number of threads started/**/
CONSOLE_SCREEN_BUFFER_INFO csbiInfo; /* Console information/**/
COORD   consoleSize;
BOOL    bTrails;

int 
C_WIN32_multithread(
    const int argc,
    char* argv[]
) /* Thread One/**/
{
    /* Get display screen information & clear the screen/**/
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
    consoleSize.X = csbiInfo.srWindow.Right;
    consoleSize.Y = csbiInfo.srWindow.Bottom;
    ClearScreen();
    WriteTitle(0);

    /*  Create the mutexes and reset thread count./**/
    hScreenMutex = CreateMutexW(NULL, FALSE, NULL);  /*  Cleared/**/
    hRunMutex = CreateMutexW(NULL, TRUE, NULL);      /*  Set/**/
    ThreadNr = 0;
    bTrails = FALSE;

    /*  Start waiting for keyboard input to dispatch threads or exit./**/
    KbdFunc();

    /*  All threads done. Clean up handles./**/
    if (hScreenMutex) CloseHandle(hScreenMutex);
    if (hRunMutex) CloseHandle(hRunMutex);
    if (hConsoleOut) CloseHandle(hConsoleOut);

    return 0;
}

void ShutDown(void) /*  Shut down threads/**/
{
    while (ThreadNr > 0)
    {
        /*  Tell thread to die and record its death./**/
        ReleaseMutex(hRunMutex);
        ThreadNr--;
    }

    /*  Clean up display when done/**/
    WaitForSingleObject(hScreenMutex, INFINITE);
    ClearScreen();
}

void KbdFunc(void) /*  Dispatch and count threads./**/
{
    int         KeyInfo;

    do
    {
        KeyInfo = _getch();
        if (tolower(KeyInfo) == 'a' &&
            ThreadNr < MAX_THREADS)
        {
			ThreadNr++;

			_beginthread(/*Magic in here*/
				BounceProc,
				0,
				&ThreadNr);

			WriteTitle(ThreadNr);
		}
        if (tolower(KeyInfo) == 't')
        {
            bTrails = !bTrails;
        }
    } while (tolower(KeyInfo) != 'q');

    ShutDown();

#define ATTEMPT 0
#if ATTEMPT == 1
    int* Foo(char, double);
    char ch;
    double dbl;
    _beginthread(Foo, 0, &ch, &dbl);/**/
#endif
}

void BounceProc(void* pMyID)
{
    wchar_t MyCell, OldCell;
    WORD    MyAttrib, OldAttrib = 0;
    wchar_t BlankCell = 0x20;
    COORD   Coords, Delta;
    COORD   Old = { 0,0 };
    DWORD   Dummy;
    char* MyID = (char*)pMyID;

    /*  Generate update increments and initial/**/
    /*  display coordinates./**/
    srand((unsigned int)*MyID * 3);

    Coords.X = GET_RAND(0, consoleSize.X - 1);
    Coords.Y = GET_RAND(0, consoleSize.Y - 1);
    Delta.X = GET_RAND(-3, 3);
    Delta.Y = GET_RAND(-3, 3);

    /*  Set up character & generate color/**/
    /*  attribute from thread number./**/
    if (*MyID > 16)
        MyCell = 0x60 + *MyID - 16; /*  lower case/**/
    else
        MyCell = 0x40 + *MyID;      /*  upper case/**/
    MyAttrib = *MyID & 0x0f;   /*  force black background/**/

    do
    {
        /*  Wait for display to be available, then lock it./**/
        WaitForSingleObject(hScreenMutex, INFINITE);

        if (!bTrails)
        {
            /*  If we still occupy the old screen position, blank it out./**/
            ReadConsoleOutputCharacterW(hConsoleOut, &OldCell, 1,
                Old, &Dummy);
            ReadConsoleOutputAttribute(hConsoleOut, &OldAttrib, 1,
                Old, &Dummy);
            if ((OldCell == MyCell) && (OldAttrib == MyAttrib))
                WriteConsoleOutputCharacterW(hConsoleOut, &BlankCell, 1,
                    Old, &Dummy);
        }

        /*  Draw new character, then clear screen lock/**/
        WriteConsoleOutputCharacterW(
            hConsoleOut,
            &MyCell,
            1,
            Coords,
            &Dummy);
        WriteConsoleOutputAttribute(
            hConsoleOut,
            &MyAttrib,
            1,
            Coords,
            &Dummy);
        /*  Unlock display./**/
        ReleaseMutex(hScreenMutex);

        /*  Increment the coordinates for next placement of the block./**/
        Old.X = Coords.X;
        Old.Y = Coords.Y;
        Coords.X += Delta.X;
        Coords.Y += Delta.Y;

        /*  If we are about to go off the screen, reverse direction/**/
        if (Coords.X < 0 || Coords.X >= consoleSize.X)
        {
            Delta.X = -Delta.X;
            Beep(400, 50);
        }
        if (Coords.Y < 0 || Coords.Y > consoleSize.Y)
        {
            Delta.Y = -Delta.Y;
            Beep(600, 50);
        }
    }
    /*  Repeat while RunMutex is still taken./**/
    while (WaitForSingleObject(hRunMutex, 75L) == WAIT_TIMEOUT);
}

void WriteTitle(int ThreadNum)
{
    enum
    {
        sizeOfNThreadMsg = 120
    };
    wchar_t    NThreadMsg[sizeOfNThreadMsg] = { L"" };

    /* write the format string in the "NThreadMsg[sizeOfNThreadMsg]"-buffer/**/
    swprintf_s(
        NThreadMsg,
        sizeOfNThreadMsg,
        L"Threads running: %02d.  Press 'A' "
        L"to start a thread, 'T' to toggle "
        L"trails, 'Q' to quit.",
        ThreadNum
    );

    /*printing "NThreadMsg[sizeOfNThreadMsg]" in the console title /**/
    SetConsoleTitleW(NThreadMsg);
}

void ClearScreen(void)
{
    DWORD    dummy = 0;
    COORD    Home = { 0, 0 };
    FillConsoleOutputCharacterW(
        hConsoleOut,
        L' ',
        consoleSize.X * consoleSize.Y,
        Home,
        &dummy);
}
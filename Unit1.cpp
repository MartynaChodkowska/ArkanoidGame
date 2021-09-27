//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

int x = -8, y = -8;
bool gameOn = false;
int paddle1score = 0, paddle2score = 0;
int bounceCounting = 0;

void gameReset()
{
        gameOn = true;
        Form1->startGame->Visible = false;
        Form1->onceAgain->Visible = false;
        Form1->paddle1scoreTable->Visible = false;
        Form1->paddle2scoreTable->Visible = false;
        Form1->paddle1->Picture->LoadFromFile("img/paddle.bmp");
        Form1->paddle2->Picture->LoadFromFile("img/paddle.bmp");
        Form1->paddle1->Top = 100;
        Form1->paddle2->Top = 100;
        Form1->ball->Left = 400;
        Form1->ball->Top = 120;
        Form1->ball->Visible = true;
        Form1->ballMovement->Enabled = true;
}

void gameOver(int winningPaddle)
{
                Form1->ballMovement->Enabled = false;
                Form1->ball->Visible = false;

                switch (winningPaddle)
                {
                        case 1:
                        {
                                Form1->paddle1->Picture->LoadFromFile("img/winningPaddle1.bmp");

                        }break;
                        case 2:
                        {
                                Form1->paddle2->Picture->LoadFromFile("img/winningPaddle1.bmp");
                        }break;
                }
                Form1->paddle1scoreTable->Caption = IntToStr(paddle1score);
                Form1->paddle2scoreTable->Caption = IntToStr(paddle2score);
                Form1->paddle1scoreTable->Visible = true;
                Form1->paddle2scoreTable->Visible = true;
                Form1->onceAgain->Visible = true;
                Form1->startGame->Visible = true;
                gameOn = false;
}


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ballMovementTimer(TObject *Sender)
{
        ball->Left += x;
        ball->Top += y;

      //odbij od gornej sciany
        if(ball->Top-5 <= tlo->Top) y = -y;
      //odbij od dolnej sciany
        if(ball->Top+ ball->Height >= tlo->Top+tlo->Height) y = -y;

      //przegrana paddle1, wygrana paddle2
        if(ball->Left <= paddle1->Left+paddle1->Width/2 &&
           (ball->Top > paddle1->Top+paddle1->Height||
            ball->Top+ball->Height < paddle1->Top))
        {
                paddle2score++;
                gameOver(2);
        }
      //przegrana paddle2, wygrana paddle1
        else if(ball->Left+ball->Width >= paddle2->Left &&
               (ball->Top > paddle2->Top+paddle2->Height||
                ball->Top+ball->Height < paddle2->Top))
        {
                paddle1score++;
                gameOver(1);
        }
      //odbicie paddle1
       else if(ball->Left <= paddle1->Left+paddle1->Width &&
           ball->Top < paddle1->Top+paddle1->Height &&
           ball->Top+ball->Height > paddle1->Top)
        {
                x = -x;
                bounceCounting++;
        }
     //odbicie paddle2
        else if(ball->Left+ball->Width >= paddle2->Left &&
           ball->Top < paddle2->Top+paddle2->Height &&
           ball->Top+ball->Height > paddle2->Top)
        {
                x = -x;
                bounceCounting++;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddle1UpTimer(TObject *Sender)
{
        if (paddle1->Top > tlo->Top+10) paddle1->Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddle1DownTimer(TObject *Sender)
{
        if (paddle1->Top+paddle1->Height < tlo->Top+tlo->Height-10) paddle1->Top +=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddle2UpTimer(TObject *Sender)
{
        if (paddle2->Top > tlo->Top+10) paddle2->Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddle2DownTimer(TObject *Sender)
{
        if (paddle2->Top+paddle2->Height  < tlo->Top+tlo->Height-10) paddle2->Top +=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(gameOn)
        {
                if (Key == 'A') paddle1Up->Enabled = true;
                if (Key == 'Z') paddle1Down->Enabled = true;
                if (Key == VK_UP) paddle2Up->Enabled = true;
                if (Key == VK_DOWN) paddle2Down->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 'A') paddle1Up->Enabled = false;
        if (Key == 'Z') paddle1Down->Enabled = false;
        if (Key == VK_UP) paddle2Up->Enabled = false;
        if (Key == VK_DOWN) paddle2Down->Enabled = false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{
        if(Application->MessageBox("Witaj w grze!\nLewy gracz steruje wciskaj¹c klawisze A oraz Z.\nPrawy gracz - strza³ki do góry oraz w dó³.\n\n\ HaveFun!", "Gramy?",
           MB_OK | MB_ICONINFORMATION) == IDOK)
           {
                startGame->Visible = true;
           }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::startGameClick(TObject *Sender)
{
        paddle1score = 0;
        paddle2score = 0;
        gameReset();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::onceAgainClick(TObject *Sender)
{
        gameReset();
}
//---------------------------------------------------------------------------


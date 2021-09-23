//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

int x = -8, y = -8;

TForm1 *Form1;
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
      //odbij od lewej sciany
        if(ball->Left-5 <= tlo->Left)   x = -x;
      //odbij od prawej sciany
         if(ball->Left+ball->Width+5 >= tlo->Width) x = -x;


}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddle1UpTimer(TObject *Sender)
{
        if (paddle1->Top > tlo->Top-10) paddle1->Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddle1DownTimer(TObject *Sender)
{
        if (paddle1->Top+paddle1->Height < tlo->Top+tlo->Height+10) paddle1->Top +=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddle2UpTimer(TObject *Sender)
{
        if (paddle2->Top > tlo->Top-10) paddle2->Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddle2DownTimer(TObject *Sender)
{
        if (paddle2->Top+paddle2->Height  < tlo->Top+tlo->Height+10) paddle2->Top +=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 'A') paddle1Up->Enabled = true;
        if (Key == 'Z') paddle1Down->Enabled = true;
        if (Key == VK_UP) paddle2Up->Enabled = true;
        if (Key == VK_DOWN) paddle2Down->Enabled = true;
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

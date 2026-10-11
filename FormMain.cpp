//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormMain.h"
#include "FormFind.h"
#include <Vcl.Printers.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmMain *FrmMain;
//---------------------------------------------------------------------------
__fastcall TFrmMain::TFrmMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::MenuAboutClick(TObject *Sender)
{
	Application->MessageBoxW(L"Created by Brandon", L"About Text Editor", MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::EditCutClick(TObject *Sender)
{
	Memo->CutToClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::EditCopyClick(TObject *Sender)
{
	Memo->CopyToClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::EditPasteClick(TObject *Sender)
{
	Memo->PasteFromClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::MenuWrapClick(TObject *Sender)
{
	MenuWrap->Checked = !MenuWrap->Checked;
	Memo->WordWrap = MenuWrap->Checked;
	if (Memo->WordWrap) {
		Memo->ScrollBars = ssVertical;
	} else Memo->ScrollBars = ssBoth;
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::FontColorClick(TObject *Sender)
{
	ColorDialog->Color = Memo->Font->Color;
	if (ColorDialog->Execute()) {
		Memo->Font->Color = ColorDialog->Color;
	}

}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::BackColorClick(TObject *Sender)
{
	ColorDialog->Color = Memo->Color;
	if (ColorDialog->Execute()) {
		Memo->Color = ColorDialog->Color;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::FontClick(TObject *Sender)
{
	FontDialog->Font = Memo->Font;
	if (FontDialog->Execute()) {
		Memo->Font = FontDialog->Font;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::FormCreate(TObject *Sender)
{
   modified = false;
   Filename = "";

}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::MemoChange(TObject *Sender)
{
	modified = true;
	StatusBar->Panels->Items[0]->Text = "Modified";
}
//---------------------------------------------------------------------------

void __fastcall TFrmMain::FileSaveAClick(TObject *Sender)
{
	SaveDialog->FileName = Filename;
	if (SaveDialog->Execute()) {
		Filename = SaveDialog->FileName;
		Memo->Lines->SaveToFile(Filename);
		modified = false;
		StatusBar->Panels->Items[0]->Text = "";
		canContinue = true;
	} else canContinue = false;
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::FileSaveClick(TObject *Sender)
{
	if (Filename == "") {
		FileSaveAClick(FileSave);
	} else {
		Memo->Lines->SaveToFile(Filename);
		modified = false;
		StatusBar->Panels->Items[0]->Text = "";
	}
	canContinue = true;
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::ExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TFrmMain::FileNewClick(TObject *Sender)
{
	if (modified) {
		dlgResult = Application->MessageBoxW(L"There's unsaved changes\n\nDo you want to save?", L"Save Changes!", MB_ICONINFORMATION + MB_YESNOCANCEL);

		switch (dlgResult) {
			case IDYES:
				if (Filename == "") {
					FileSaveAClick(FileNew);

				} else FileSaveClick(FileNew);

				break;

			case IDNO:
				canContinue = true;
				break;

			case IDCANCEL:
				canContinue = false;
				break;
		}
	} else canContinue = true;

	if (canContinue) {
		modified = false;
		Filename = "";
		Memo->Lines->Clear();
		StatusBar->Panels->Items[0]->Text = "";
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrmMain::FileOpenClick(TObject *Sender)
{
    if (modified) {
		dlgResult = Application->MessageBoxW(L"There's unsaved changes\n\nDo you want to save?", L"Save Changes!", MB_ICONINFORMATION + MB_YESNOCANCEL);

		switch (dlgResult) {
			case IDYES:
				if (Filename == "") {
					FileSaveAClick(FileNew);

				} else FileSaveClick(FileNew);

				break;

			case IDNO:
				canContinue = true;
				break;

			case IDCANCEL:
				canContinue = false;
				break;
		}
	} else canContinue = true;

	if (canContinue) {
		if (OpenDialog->Execute()) {
			Filename = OpenDialog->FileName;
			Memo->Lines->LoadFromFile(Filename);
			modified = false;
			StatusBar->Panels->Items[0]->Text = "";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
    if (modified) {
		dlgResult = Application->MessageBoxW(L"There's unsaved changes\n\nDo you want to save?", L"Save Changes!", MB_ICONINFORMATION + MB_YESNOCANCEL);

		switch (dlgResult) {
			case IDYES:
				if (Filename == "") {
					FileSaveAClick(FileNew);

				} else FileSaveClick(FileNew);

				break;

			case IDNO:
				canContinue = true;
				break;

			case IDCANCEL:
				canContinue = false;
				break;
		}
	} else canContinue = true;

	if (canContinue == false) {
		Action = caNone;       //caHide, caFree
	}
}
//---------------------------------------------------------------------------


void __fastcall TFrmMain::FilePrintClick(TObject *Sender)
{
	TPrinter *prn = Printer();

	if (PrintDialog->Execute()) {
		prn->BeginDoc();
		prn->Canvas->Font->Name = Memo->Font->Name;
		prn->Canvas->Font->Size = Memo->Font->Size;
		prn->Canvas->Font->Color = Memo->Font->Color;
		prn->Canvas->TextOutW(10, 10, Memo->Lines->Text); //10, 10 represents the X,Y spacing from the initial text
		prn->EndDoc();
	}
}
//---------------------------------------------------------------------------

void TFrmMain::showStatusDoc() {
	int Rpos, Cpos; //Row, Colloumn

	Rpos = SendMessage(Memo->Handle, EM_LINEFROMCHAR, Memo->SelStart, 0); //Row
	Cpos = SendMessage(Memo->Handle, EM_LINEINDEX, Rpos, 0); //Colloumn
	Cpos = Memo->SelStart - Cpos;
	StatusBar->Panels->Items[1]->Text = IntToStr(Cpos + 1) + " " + IntToStr(Rpos + 1);
}
void __fastcall TFrmMain::MemoClick(TObject *Sender)
{
	showStatusDoc();
}
//---------------------------------------------------------------------------

void __fastcall TFrmMain::MemoKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
	showStatusDoc();
	StatusBar->Panels->Items[2]->Text = IntToStr(Memo->SelStart) + " | " + IntToStr(Memo->SelLength) + " | " + Memo->SelText;
}
//---------------------------------------------------------------------------


void __fastcall TFrmMain::FindReplaceClick(TObject *Sender)
{
	FrmFind->Show();
	FrmFind->BringToFront();
}
//---------------------------------------------------------------------------


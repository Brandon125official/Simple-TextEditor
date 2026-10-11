//---------------------------------------------------------------------------

#ifndef FormFindH
#define FormFindH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFrmFind : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TEdit *txtFind;
	TEdit *txtReplace;
	TButton *btnFind;
	TButton *btnReplace;
	TMemo *Memo;
	TPanel *txtPanel;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnFindClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFrmFind(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmFind *FrmFind;
//---------------------------------------------------------------------------
#endif

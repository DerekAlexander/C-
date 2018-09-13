//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// NOTE!!!
//This was a fully realized game made by a team  over one semester consisting of Derek Alexander, Ethan Gatlin, Steven Killen, Matthew Strawn and with 
//plenty of help from our professor Scott Strentzsch aka our fearless leader. As this was a team project this is all I feel comfortable 
//showing of our work which consist of over 60 files of code as well as art and sound assets. An important note, 
//this was our own hand written engine from windows up to directx and finally to our game no SDKs here.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "stdafx.h"

#include <sstream>
#include <istream>
#include <fstream>

#include "DxFramework/DxSoundBase.h"
#include "Breakout/AssetManager.h"
#include "Breakout/BreakOut.h"


INT_PTR CALLBACK    About( HWND, UINT, WPARAM, LPARAM );

static tstring winMainCmdLineStr;

//----------------------------------------------------------------------------------------
//main fuction ~entry point into program
int APIENTRY wWinMain( _In_ HINSTANCE hInstance,
                       _In_opt_ HINSTANCE hPrevInstance,
                       _In_ LPWSTR    lpCmdLine,
                       _In_ int       nCmdShow )
{
   if ( lpCmdLine != nullptr && *lpCmdLine != TEXT('\0') )
      winMainCmdLineStr = lpCmdLine;

   Logging::logMsg( TEXT("WinMain( %s ) %d %f\n"), TEXT("Got Here!"), 100, 0.110f );
   WinFramework::enableCRTHeapDebugging(false);
   //WinFramework::breakOnCRTAlloc(6645);

   Breakout* app = new Breakout;
   int rv = app->winMain( hInstance, hPrevInstance, lpCmdLine, nCmdShow );
   delete app;
   
   return rv;
}

//----------------------------------------------------------------------------------------
//

// Message handler for about box.
INT_PTR CALLBACK About( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
   UNREFERENCED_PARAMETER( lParam );
   switch ( message )
   {
   case WM_INITDIALOG:
      return (INT_PTR)TRUE;

   case WM_COMMAND:
      if ( LOWORD( wParam ) == IDOK || LOWORD( wParam ) == IDCANCEL )
      {
         EndDialog( hDlg, LOWORD( wParam ) );
         return (INT_PTR)TRUE;
      }
      break;
   }
   return (INT_PTR)FALSE;
}

//----------------------------------------------------------------------------------------
//-----------------------------class functions--------------------------------------------
//----------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------
// constructor
Breakout::Breakout ( void )
{

}

//----------------------------------------------------------------------------------------
// deconstructor
Breakout::~Breakout ( void )
{
   LOGFUNCTION();
}


//----------------------------------------------------------------------------------------
// initializes game ~ all game objects needed at start
void Breakout::gameInit ()
{
   bool goodAssets = AssetManager::setAssetPath( TEXT("..\\..\\dev\\Assets") );  // THIS HARDCODED PATH IS DEVELOPMENT ONLY.
   if ( !goodAssets )
   {
      if ( !winMainCmdLineStr.empty() )
         goodAssets = AssetManager::setAssetPath( winMainCmdLineStr );  // THIS HARDCODED PATH IS DEVELOPMENT ONLY.

      if ( !goodAssets )
         goodAssets = AssetManager::setAssetPath( TEXT("Assets") );  // THIS HARDCODED PATH IS DEVELOPMENT ONLY.
   }

   if ( !goodAssets )
   {
      MessageBox( hWindow(), TEXT("Assets folder unavailable"), TEXT("Assets Initialization failed"), MB_OK|MB_ICONHAND );
      exit(0);
   }


   difficulty = demo;

   myLevel = new Level;
   myLevel->init( this, 768 , 768, 0, 0  );

   myLevel->registerEvent( this );


   myStartScreen = new StartScreen;
   myStartScreen->init( dxDevice(), dxSprite(), myLevel, 1024, 768, 0, 0 );

   myCreditScreen = new CreditsScreen;
   myCreditScreen->init( dxDevice(), dxSprite(), myLevel, 1024, 768, 0, 0 );

   myEndScreen = new EndScreen;
   myEndScreen->init( dxDevice(), dxSprite(), myLevel, 1024, 768, 0, 0 );

   myStatusBar = new StatusBar;
   myStatusBar->init( dxDevice(), dxSprite(), myLevel, 256, 768, 768, 0 );
   myCurrentGameRunPtr = &Breakout::startScreenRun;
   // myCurrentGameRunPtr = &Breakout::highScoresGameRun;

   myHighScores = new HighScore;
   myHighScores->init( dxDevice(), dxSprite(), myLevel, 1024, 768, 0, 0 );
   myHighScores->load( TEXT( "HighScore.txt" ) );

   //DxSoundBase::noSoundSystem( );
   mySounds = new Sounds;
   mySounds->init( myLevel );

   DxKeyboard::getInstance().init( hWindow() );
   DxMouse::getInstance().init( hWindow() );

   setFramerate( 60 );

   tstringstream ss;  
   ss << TEXT( "Arkanoid" );
   winChangeTitle( ss.str().c_str() );

   myStatusBar->update();
   myLevel->dispatchEvent( gameStart );

   myEscapeMenuCoolDownTimer = 0;
}

//----------------------------------------------------------------------------------------
//
void Breakout::gameRun ()
{

   dxDevice()->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 200, 200, 200 ), 1.0f, 0 );
   DxKeyboard::getInstance().update();
   DxMouse::getInstance().update();
   DxSoundBase::getInstance().update();
   //TODO: anything else that should be globally updated???????

   bool isCtrl = DxKeyboard::getInstance().isKeyPressed(DIK_LCONTROL) || DxKeyboard::getInstance().isKeyPressed(DIK_RCONTROL);
   if ( isCtrl )
   {
      if ( DxKeyboard::getInstance().isKeyPressed(DIK_F9))
         DxSoundBase::getInstance().togglePause();

      if (DxKeyboard::getInstance().isKeyPressed(DIK_F10))
         DxSoundBase::getInstance().toggleMute();
   }


   return  (this->*myCurrentGameRunPtr)();

}


//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

void Breakout::playingGameRun ()
{

   myLevel->update(dxDevice(), dxSprite());

   dxDevice()->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 64, 64, 64 ), 1.0f, 0 );



   if( DxMouse::getInstance().xPos() >= myStatusBar->xPos() )
      myStatusBar->update();

   //start rendering         
   if ( SUCCEEDED(dxDevice()->BeginScene()) )
   {
      if ( SUCCEEDED(dxSprite()->Begin( D3DXSPRITE_ALPHABLEND )) )
      {
         myLevel->draw( dxSprite() );
         myStatusBar->draw();

         dxSprite()->End();

      }

      stopRender(); 

      present();     
   }

   //check for escape key (to exit program)
   if ( winKeyIsDown(VK_ESCAPE) )
   {
      myEscapeMenuCoolDownTimer = 30;
      myCurrentGameRunPtr = &Breakout::startScreenRun;
   }

   if ( myLevel->getNumLives() == 0 ) 
   {
      //myCurrentGameRunPtr = &Breakout::endScreenRun;
      myLevel->pause( true );
   }
}

//----------------------------------------------------------------------------------------
//

void Breakout::startScreenRun ()
{
   myStartScreen->update();
   //myLevel->resetGame(); this breaks things radically 
   if (DxKeyboard::getInstance().isKeyPressed( DIK_F5 ) )
   {
      myCurrentGameRunPtr = &Breakout::playingGameRun;
   }


   dxDevice()->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 192, 0 ), 1.0f, 0 );

   //start rendering
   if ( SUCCEEDED( dxDevice()->BeginScene() ) )
   {

      if ( SUCCEEDED( dxSprite()->Begin( D3DXSPRITE_ALPHABLEND ) ) )
      {
         myStartScreen->draw();
         dxSprite()->End();
      }

      stopRender();
      present();
   }

   //check for escape key (to exit program)
   if ( winKeyIsDown( VK_ESCAPE ) && myEscapeMenuCoolDownTimer == 0 )
   {
      PostMessage( hWindow(), WM_DESTROY, 0, 0 );
   }
   else if ( myEscapeMenuCoolDownTimer > 0 )
      myEscapeMenuCoolDownTimer--;
}


//----------------------------------------------------------------------------------------
//
void Breakout::creditsGameRun ( )
{

   dxDevice()->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 192, 0 ), 1.0f, 0 );

   myCreditScreen->update();

   //start rendering
   if ( SUCCEEDED( dxDevice()->BeginScene() ) )
   {

      if ( SUCCEEDED( dxSprite()->Begin( D3DXSPRITE_ALPHABLEND ) ) )
      {
         myCreditScreen->draw();
         dxSprite()->End();
}

      stopRender();
      present();
   }

   //check for escape key (to exit program)
   if ( winKeyIsDown( VK_ESCAPE ) )
   {
      myEscapeMenuCoolDownTimer = 30;
      myCurrentGameRunPtr = &Breakout::startScreenRun;
   }

}

//----------------------------------------------------------------------------------------
//
void Breakout::highScoresGameRun ( )
{
   myHighScores->update();

   dxDevice()->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 192, 0 ), 1.0f, 0 );

   //start rendering
   if ( SUCCEEDED( dxDevice()->BeginScene() ) )
   {

      if ( SUCCEEDED( dxSprite()->Begin( D3DXSPRITE_ALPHABLEND ) ) )
      {
         myHighScores->draw();
         dxSprite()->End();
      }

      stopRender();
      present();
   }

   //check for escape key (to exit program)
   if ( winKeyIsDown( VK_ESCAPE ) )
   {
      myEscapeMenuCoolDownTimer = 30;
      myCurrentGameRunPtr = &Breakout::startScreenRun;
   }
}

//----------------------------------------------------------------------------------------
//
void Breakout::endScreenRun ( )
{
   myEndScreen->update();

   dxDevice()->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 192, 0 ), 1.0f, 0 );

   //start rendering
   if ( SUCCEEDED( dxDevice()->BeginScene() ) )
   {

      if ( SUCCEEDED( dxSprite()->Begin( D3DXSPRITE_ALPHABLEND ) ) )
      {
         myEndScreen->draw();
         dxSprite()->End();
      }

      stopRender();
      present();
   }

   //check for escape key (to exit program)
   if ( winKeyIsDown( VK_ESCAPE ) )
   {
      myEscapeMenuCoolDownTimer = 30;
      myCurrentGameRunPtr = &Breakout::startScreenRun;
}
}

//----------------------------------------------------------------------------------------
//
void Breakout::gameOverGameRun ( )
{

   if (DxKeyboard::getInstance().isKeyPressed( DIK_F5 ) )
   {

      myCurrentGameRunPtr = &Breakout::playingGameRun;
   }


   dxDevice()->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 128 ), 1.0f, 0 );

   //start rendering
   if ( SUCCEEDED( dxDevice()->BeginScene() ) )
   {

      if ( SUCCEEDED( dxSprite()->Begin( D3DXSPRITE_ALPHABLEND ) ) )
      {
         dxSprite()->End();
      }

      stopRender();
      present();
   }

   //check for escape key (to exit program)
   if ( winKeyIsDown( VK_ESCAPE ) )
   {
      myEscapeMenuCoolDownTimer = 30;
      myCurrentGameRunPtr = &Breakout::startScreenRun;
}
}


void Breakout::processEvent ( unsigned msg, int lVal, int rVal )
{
   switch ( msg )
   {
   case buttonClicked:
      if ( lVal == myStartScreen->tag() && rVal == myStartScreen->easyButtonTag() )
      {
         difficulty = easy;
         myLevel->setDifficultyLevel( );
         myLevel->resetGame();
         myCurrentGameRunPtr = &Breakout::playingGameRun;
      }
      else if ( lVal == myStartScreen->tag() && rVal == myStartScreen->mediumButtonTag() )
      {
         difficulty = medium;
         myLevel->setDifficultyLevel( );
         myLevel->resetGame();
         myCurrentGameRunPtr = &Breakout::playingGameRun;
      }
      else if ( lVal == myStartScreen->tag() && rVal == myStartScreen->hardButtonTag() )
      {
         difficulty = hard;
         myLevel->setDifficultyLevel( );
         myLevel->resetGame();
         myCurrentGameRunPtr = &Breakout::playingGameRun;
      }
      else if ( lVal == myStartScreen->tag() && rVal == myStartScreen->creditsButtonTag() )
         myCurrentGameRunPtr = &Breakout::creditsGameRun;
      else if ( lVal == myEndScreen->tag() && rVal == myEndScreen->startButtonTag() )
         myCurrentGameRunPtr = &Breakout::startScreenRun;

      else if ( lVal == myEndScreen->tag() && rVal == myEndScreen->highScoreButtonTag() )
      {
         myHighScores->addScore( this->myLevel->getScore());
         myCurrentGameRunPtr = &Breakout::highScoresGameRun;
      }
      else if ( lVal == myHighScores->tag() && rVal == myHighScores->backButtonTag() )
         myCurrentGameRunPtr = &Breakout::startScreenRun;
      else if (lVal == myCreditScreen->tag() && rVal == myCreditScreen->backButtonTag() )
         myCurrentGameRunPtr = &Breakout::startScreenRun;

      else if (lVal == myStartScreen->tag() && rVal == myStartScreen->ExitButtonTag() )
         PostMessage( hWindow(), WM_DESTROY, 0, 0 );
      break;

   case gameCompleted:
      myCurrentGameRunPtr = &Breakout::endScreenRun;
      break;
   case gameLost:
      myCurrentGameRunPtr = &Breakout::endScreenRun;
      break;
   }
}


void Breakout::gameShutdown ( )
{

   deleteDynPtr( mySounds );
   deleteDynPtr( myStatusBar );
   deleteDynPtr( myLevel );
   deleteDynPtr( myEndScreen );
   deleteDynPtr( myStartScreen );
   deleteDynPtr( myCreditScreen );
   deleteDynPtr( myHighScores );

   DxKeyboard::releaseInstance();
   DxMouse::releaseInstance();

   AssetManager::release();
}

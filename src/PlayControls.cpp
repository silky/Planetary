/*
 *  PlayControls.h
 *  Kepler
 *
 *  Created by Tom Carden on 3/7/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "PlayControls.h"
#include "Globals.h"
#include "BloomGl.h"
#include "BloomScene.h" // for mRoot

using namespace ci;
using namespace ci::app;
using namespace std;

void PlayControls::setup( Vec2f interfaceSize, ipod::Player *player, const Font &font, const Font &fontSmall, const gl::Texture &uiBigButtonsTex, const gl::Texture &uiSmallButtonsTex )
{   

    // create, add, and position everything...
    createChildren( font, fontSmall, uiBigButtonsTex, uiSmallButtonsTex );
    setInterfaceSize( interfaceSize );
        
    // set initial state...
    setPlaying( player->getPlayState() == ipod::Player::StatePlaying );    
    setOrbitsVisible( G_DRAW_RINGS );
    setLabelsVisible( G_DRAW_TEXT );
//    setHelpVisible( G_HELP );
    setDebugVisible( G_DEBUG );	    
    setShuffleVisible( player->getShuffleMode() != ipod::Player::ShuffleModeOff );
    setRepeatMode( player->getRepeatMode() );    
    setAlphaWheelVisible( false ); // this is the default in KeplerApp::remainingSetup()
    if( G_IS_IPAD2 ) {
        setGyroVisible( G_USE_GYRO );
    }
}

void PlayControls::createChildren( const Font &font, const Font &fontSmall, const gl::Texture &uiBigButtonsTex, const gl::Texture &uiSmallButtonsTex )
{
	float uw = uiBigButtonsTex.getWidth() / 4.0f;   // button tex width
	float uh = uiBigButtonsTex.getHeight() / 4.0f;	// button tex height

    mGalaxyButton = new SimpleButton( GOTO_GALAXY,   // ID
                                      uiBigButtonsTex,
                                      Area( uw*0, uh*1, uw*1, uh*2 ),  // on texture
                                      Area( uw*0, uh*0, uw*1, uh*1 ) );// off texture
    
    mCurrentTrackButton = new SimpleButton( GOTO_CURRENT_TRACK,   // ID
                                            uiBigButtonsTex,
                                            Area( uw*1, uh*1, uw*2, uh*2 ),  // on texture
                                            Area( uw*1, uh*0, uw*2, uh*1 ) );// off texture

	mShowSettingsButton = new ToggleButton( SETTINGS, 
                                            false, 
                                            uiBigButtonsTex,
                                            Area( uw*2, uh*1, uw*3, uh*2 ),  // on texture
                                            Area( uw*2, uh*0, uw*3, uh*1 ) );// off texture   

    mPreviousTrackButton = new SimpleButton( PREV_TRACK, 
                                             uiBigButtonsTex,
                                             Area( uw*3, uh*1, uw*4, uh*2 ),  // on texture
                                             Area( uw*3, uh*0, uw*4, uh*1 ) );// off texture
	
    mPlayPauseButton = new TwoStateButton( PLAY_PAUSE, 
                                           false, // initial state is updated in setup()
                                           uiBigButtonsTex,
                                           Area( uw*0, uh*3, uw*1, uh*4 ),  // offDown   
                                           Area( uw*0, uh*2, uw*1, uh*3 ),  // offUp
                                           Area( uw*1, uh*3, uw*2, uh*4 ),  // onDown
                                           Area( uw*1, uh*2, uw*2, uh*3 ) );// onUp

    mNextTrackButton = new SimpleButton( NEXT_TRACK, 
                                         uiBigButtonsTex,
                                         Area( uw*2, uh*3, uw*3, uh*4 ),  // on texture
                                         Area( uw*2, uh*2, uw*3, uh*3 ) );// off texture
	
    mAlphaWheelButton = new ToggleButton( SHOW_WHEEL,      // ID
                                          false,           // initial toggle state
                                          uiBigButtonsTex,
                                          Area( uw*3, uh*3, uw*4, uh*4 ),  // on texture
                                          Area( uw*3, uh*2, uw*4, uh*3 ) );// off texture    

    
     

    // !!! SMALL BUTTONS !!!
    uw = uiSmallButtonsTex.getWidth() / 5.0f;
	uh = uiSmallButtonsTex.getHeight() / 5.0f;

    {
//        mHelpButton = new ToggleButton( HELP, 
//                                        false, 
//                                        uiSmallButtonsTex,
//                                        Area( uw*0, uh*1, uw*1, uh*2 ),  // on texture
//                                        Area( uw*0, uh*0, uw*1, uh*1 ) ); // off texture
        
		if( G_IS_IPAD2 ){
			mGyroButton = new ToggleButton( USE_GYRO, 
                                            false, 
                                            uiSmallButtonsTex,
                                            Area( uw*1, uh*1, uw*2, uh*2 ),  // on texture
                                            Area( uw*1, uh*0, uw*2, uh*1 ) ); // off texture
		}
        mScreensaverButton = new ToggleButton( AUTO_MOVE,
											   false,
											   uiSmallButtonsTex,
											   Area( uw*4, uh*3, uw*5, uh*4 ),
											   Area( uw*4, uh*2, uw*5, uh*3 ) );
		
        mOrbitsButton = new ToggleButton( DRAW_RINGS, 
                                          false, 
                                          uiSmallButtonsTex,
                                          Area( uw*2, uh*1, uw*3, uh*2 ),  // on texture
                                          Area( uw*2, uh*0, uw*3, uh*1 ) ); // off texture

        mLabelsButton = new ToggleButton( DRAW_TEXT, 
                                          false, 
                                          uiSmallButtonsTex,
                                          Area( uw*3, uh*1, uw*4, uh*2 ),  // on texture
                                          Area( uw*3, uh*0, uw*4, uh*1 ) ); // off texture

        mDebugButton = new ToggleButton( DEBUG_FEATURE, 
                                         false, 
                                         uiSmallButtonsTex,
                                         Area( uw*4, uh*1, uw*5, uh*2 ),  // on texture
                                         Area( uw*4, uh*0, uw*5, uh*1 ) ); // off texture
		
		
		mShuffleButton = new ToggleButton( SHUFFLE, 
                                           false, 
                                           uiSmallButtonsTex,
                                           Area( uw*0, uh*3, uw*1, uh*4 ),  // on texture
                                           Area( uw*0, uh*2, uw*1, uh*3 ) ); // off texture
		
		mRepeatButton = new ThreeStateButton( REPEAT, 
                                          0, 
                                          uiSmallButtonsTex,
                                          Area( uw*1, uh*2, uw*2, uh*3 ),   // first texture  (off)
                                          Area( uw*1, uh*3, uw*2, uh*4 ),   // second texture (repeat all)
                                          Area( uw*2, uh*2, uw*3, uh*3 ) ); // third texture  (repeat one)
    }
    
    mPlayheadSlider = new Slider( SLIDER,          // ID
                                  uiSmallButtonsTex,
								 Area( uw*2.2f, uh*3, uw*2.3f, uh*4 ),  // bg texture
								 Area( uw*2.7f, uh*3, uw*2.8f, uh*4 ),  // fg texture
                                  Area( uw*3, uh*3, uw*4, uh*4 ),  // thumb on texture
                                  Area( uw*3, uh*2, uw*4, uh*3 )); // thumb off texture

    /////// no textures please, we're British...
    
    mTrackInfoLabel = new ScrollingLabel(NO_BUTTON, font, BRIGHT_BLUE);
    
    mElapsedTimeLabel = new TimeLabel(NO_BUTTON, fontSmall, BRIGHT_BLUE);
    
    mRemainingTimeLabel = new TimeLabel(NO_BUTTON, fontSmall, BRIGHT_BLUE);
        
    ///////
	// TODO: add initial value
	mParamSlider1 = new Slider( PARAMSLIDER1,          // ID
							   uiSmallButtonsTex,
							   Area( uw*2.2f, uh*3, uw*2.3f, uh*4 ),  // bg texture
							   Area( uw*2.7f, uh*3, uw*2.8f, uh*4 ),  // fg texture
							   Area( uw*3, uh*3, uw*4, uh*4 ),  // thumb on texture
							   Area( uw*3, uh*2, uw*4, uh*3 )); // thumb off texture
	mParamSlider1->setValue( 0.25f );
	mParamSlider1Label = new TextLabel( NO_BUTTON, font, BRIGHT_BLUE );
	mParamSlider1Label->setText( "Scale" );
	
	mParamSlider2 = new Slider( PARAMSLIDER2,          // ID
							   uiSmallButtonsTex,
							   Area( uw*2.2f, uh*3, uw*2.3f, uh*4 ),  // bg texture
							   Area( uw*2.7f, uh*3, uw*2.8f, uh*4 ),  // fg texture
							   Area( uw*3, uh*3, uw*4, uh*4 ),  // thumb on texture
							   Area( uw*3, uh*2, uw*4, uh*3 )); // thumb off texture
	mParamSlider2->setValue( 0.15f );
	mParamSlider2Label = new TextLabel( NO_BUTTON, font, BRIGHT_BLUE );
	mParamSlider2Label->setText( "Speed" );
    
    //////// little fady bits to cover the edges of scrolling bits:
    Area aLeft = Area( 0, 160, 14, 170 ); // references the uiButtons image    
    mCoverLeftTextureRect = new TextureRect( uiSmallButtonsTex, aLeft );
    // NB:- when rect is set for the right side, x1 > x2 so it is flipped
    mCoverRightTextureRect = new TextureRect( uiSmallButtonsTex, aLeft );    
}    

bool PlayControls::addedToScene()
{
    // now mRoot is valid we can add children
    addChildren(); // FIXME: make it so you can add children even if mRoot is invalid
    // add listeners to relay callbacks...
    std::cout << "registering callbacks in PlayControls" << std::endl;
    mCbTouchMoved = getRoot()->registerBloomNodeTouchMoved( this, &PlayControls::onBloomNodeTouchMoved );
    mCbTouchEnded = getRoot()->registerBloomNodeTouchEnded( this, &PlayControls::onBloomNodeTouchEnded );    
    return false;
}

bool PlayControls::removedFromScene()
{
    // remove listeners...
    // FIXME: this should also be done in destructor (?)
    getRoot()->unregisterBloomNodeTouchMoved( mCbTouchMoved );
    getRoot()->unregisterBloomNodeTouchEnded( mCbTouchEnded );    
    return false;
}

void PlayControls::addChildren()
{
    // bit of hack, these are first for batch reasons
    // (we want the little fadey bits to be drawn on top)
    addChild( BloomNodeRef(mTrackInfoLabel) );
    // shaded bits on top of scrolling mTrackInfoLabel
    addChild( BloomNodeRef(mCoverLeftTextureRect) );
    addChild( BloomNodeRef(mCoverRightTextureRect) );    
	addChild( BloomNodeRef(mPlayheadSlider) );    
    addChild( BloomNodeRef(mElapsedTimeLabel) );
    addChild( BloomNodeRef(mRemainingTimeLabel) ); 
    
    addChild( BloomNodeRef(mGalaxyButton) );
	addChild( BloomNodeRef(mCurrentTrackButton) );
    addChild( BloomNodeRef(mShowSettingsButton) );
	addChild( BloomNodeRef(mAlphaWheelButton) );
    addChild( BloomNodeRef(mPreviousTrackButton) );
    addChild( BloomNodeRef(mPlayPauseButton) );
    addChild( BloomNodeRef(mNextTrackButton) );
	
    mSettingsNodeRef = BloomNodeRef(new BloomNode());
    addChild( mSettingsNodeRef );
    mSettingsNodeRef->setVisible( G_SHOW_SETTINGS );
    mShowSettingsButton->setOn( G_SHOW_SETTINGS );     
    mSettingsNodeRef->addChild( BloomNodeRef(mShuffleButton) );
    mSettingsNodeRef->addChild( BloomNodeRef(mRepeatButton) );
	mSettingsNodeRef->addChild( BloomNodeRef(mScreensaverButton) );
//    mSettingsNodeRef->addChild( BloomNodeRef(mHelpButton) );
    mSettingsNodeRef->addChild( BloomNodeRef(mOrbitsButton) );
    mSettingsNodeRef->addChild( BloomNodeRef(mLabelsButton) );
    mSettingsNodeRef->addChild( BloomNodeRef(mDebugButton) );
    if( G_IS_IPAD2 ) mSettingsNodeRef->addChild( BloomNodeRef(mGyroButton) );
	mSettingsNodeRef->addChild( BloomNodeRef(mParamSlider1) );
	mSettingsNodeRef->addChild( BloomNodeRef(mParamSlider2) );
	mSettingsNodeRef->addChild( BloomNodeRef(mParamSlider1Label) );
    mSettingsNodeRef->addChild( BloomNodeRef(mParamSlider2Label) );    
}


bool PlayControls::onBloomNodeTouchMoved( BloomNodeRef nodeRef )
{
    if ( nodeRef->getId() == mPlayheadSlider->getId() ) {
        mCallbacksPlayheadMoved.call( mPlayheadSlider->getValue() );
    }
    return false;
}

bool PlayControls::onBloomNodeTouchEnded( BloomNodeRef nodeRef )
{
    if ( nodeRef->getId() == mPlayheadSlider->getId() ) {
        mCallbacksPlayheadMoved.call( mPlayheadSlider->getValue() );
    }
    mCallbacksButtonPressed.call(ButtonId(nodeRef->getId()));
    return false;
}

void PlayControls::setInterfaceSize( Vec2f interfaceSize )
{
    mInterfaceSize = interfaceSize;
    
	const float topBorder	 = 5.0f;
	const float sideBorder	 = 10.0f;
    
    const float bSize		 = 50.0f;
    const float bSizeSmall	 = 40.0f;
	const float buttonGap	 = 1.0f;

	const float timeTexWidth = 60.0f;
    const float sliderHeight = 20.0f;
    const float sliderInset  = bSize * 2.0f + sideBorder + timeTexWidth;
    const bool  landscape    = interfaceSize.x > interfaceSize.y;
    const float sliderWidth  = landscape ? 328.0f : 201.0f;
    
    // FLY TO CURRENT TRACK-MOON BUTTON
	float y1 = topBorder;
	float y2 = y1 + bSize;
	float x1 = sideBorder;
	float x2 = x1 + bSize;        
    mGalaxyButton->setRect( x1, y1, x2, y2 );
    
	x1 += bSize + buttonGap;
	x2 = x1 + bSize;
    mCurrentTrackButton->setRect( x1, y1, x2, y2 );

    // NEXT / PLAY-PAUSE / PREVIOUS TRACK BUTTON
    x1 = interfaceSize.x - sideBorder - bSize;
	x2 = x1 + bSize;
    mNextTrackButton->setRect( x1, y1, x2, y2 );

    x1 -= bSize + buttonGap;
	x2 = x1 + bSize;
    mPlayPauseButton->setRect( x1, y1, x2, y2 );
    
	x1 -= bSize + buttonGap;
	x2 = x1 + bSize;    
    mPreviousTrackButton->setRect( x1, y1, x2, y2 );

	x1 -= ( bSize + buttonGap ) * 2.0f;
	x2 = x1 + bSize;    
    mShowSettingsButton->setRect( x1, y1, x2, y2 );

	// ALPHA WHEEL BUTTON
	x1 -= bSize + buttonGap;
	x2 = x1 + bSize;
    mAlphaWheelButton->setRect( x1, y1, x2, y2 );
	
	
	
	y1 += 60.0f;
    y2 = y1 + bSizeSmall;
	
// SHUFFLE TOGGLE BUTTON
	x1 = interfaceSize.x - sideBorder - bSizeSmall - 3.0f;
	x2 = x1 + bSizeSmall;    
    mShuffleButton->setRect( x1, y1, x2, y2 );

// REPEAT TOGGLE BUTTON
	x1 -= bSizeSmall;
	x2 = x1 + bSizeSmall;
    mRepeatButton->setRect( x1, y1, x2, y2 );
	
// TEXT LABELS TOGGLE BUTTON
	float gap = 25.0f;
	x1 -= bSizeSmall + gap;
	x2 = x1 + bSizeSmall;
    mLabelsButton->setRect( x1, y1, x2, y2 );
	
// ORBIT RING TOGGLE BUTTON
	x1 -= bSizeSmall;
	x2 = x1 + bSizeSmall;
    mOrbitsButton->setRect( x1, y1, x2, y2 );
	
// GYRO TOGGLE BUTTON
	if( G_IS_IPAD2 ){
		x1 -= bSizeSmall;
		x2 = x1 + bSizeSmall;
		mGyroButton->setRect( x1, y1, x2, y2 );
	}
	
// DEBUG TOGGLE BUTTON
	x1 -= bSizeSmall;
	x2 = x1 + bSizeSmall;
    mDebugButton->setRect( x1, y1, x2, y2 );
	
// SCREENSAVER TOGGLE BUTTON
	x1 -= bSizeSmall;
	x2 = x1 + bSizeSmall;
    mScreensaverButton->setRect( x1, y1, x2, y2 );
	
//// HELP TOGGLE BUTTON
//    x1 -= bSizeSmall;
//	x2 = x1 + bSizeSmall;
//    mHelpButton->setRect( x1, y1, x2, y2 );
	
	
	
//// PREVIOUS PLAYLIST BUTTON
//	x1 = 10.0f;
//	x2 = x1 + bSize;
//	mPreviousPlaylistButton->setRect( x1, y1, x2, y2 );
//	
//// NEXT PLAYLIST BUTTON
//	x1 = x2;
//	x2 = x1 + bSize;
//	mNextPlaylistButton->setRect( x1, y1, x2, y2 );
//	
//// PLAYLIST LABEL
//	x1 = x2 + 10.0f;
//	x2 = x1 + 300.0f;
//	y1 += 12.0f;
//	// this 18.0f offset is a hack to make hit-testing work
//    // rect is used for layout and for hit-testing, but ScrollingLabel.draw compensates for this
//	y2 = y1 + 18.0f;
//	mPlaylistLabel->setRect( x1, y1, x2, y2 );
    
    const float bgx1 = sliderInset;
    const float bgx2 = bgx1 + sliderWidth;
    const float bgy1 = 32.0f;
    const float bgy2 = bgy1 + sliderHeight;
    mPlayheadSlider->setRect( bgx1, bgy1, bgx2, bgy2 );
	
	const float paramSliderWidth = landscape ? 250.0f : 150.0f;
	const float slider1X = 60.0f;
	const float slider2X = slider1X + paramSliderWidth + 75.0f;
	const float sliderYOff = 44.0f;
	
    mParamSlider1->setRect( slider1X, bgy1 + sliderYOff, slider1X + paramSliderWidth, bgy2 + sliderYOff );
    mParamSlider2->setRect( slider2X, bgy1 + sliderYOff, slider2X + paramSliderWidth, bgy2 + sliderYOff );
	
	mParamSlider1Label->setRect( slider1X - 40.0f, bgy1 + sliderYOff, slider1X, bgy2 + sliderYOff );
	mParamSlider2Label->setRect( slider2X - 45.0f, bgy1 + sliderYOff, slider2X, bgy2 + sliderYOff );
	
    const float ctx1 = bgx1 - 43.0f;
    const float ctx2 = bgx2 + 48.0f;
    const float cty1 = bgy1 - 16.0f;
    const float cty2 = cty1 + mTrackInfoLabel->getFontHeight();
    mTrackInfoLabel->setRect( ctx1, cty1, ctx2, cty2 );

    // FIXME: bottom right coords are made up... maybe just setPos (and getWidth) for these?
    // at least use font height for calculating y2
//    mElapsedTimeLabel->setRect( bgx1-40.0f, bgy1+2.0f, bgx1, bgy1+12.0f );
	
	mElapsedTimeLabel->setRect( ctx1 + 3.0f, bgy1+2.0f, bgx1, bgy1+12.0f );
    mRemainingTimeLabel->setRect( bgx2+18.0f, bgy1+2.0f, bgx2+58.0f, bgy1+12.0f );
}

void PlayControls::setShowSettings(bool visible)
{
    mSettingsNodeRef->setVisible(visible);
    mShowSettingsButton->setOn(visible); 
}

//void PlayControls::draw()
//{
//    std::cout << "playcontrols::draw" << std::endl;
//}

void PlayControls::update()
{
    Vec2f interfaceSize = getRoot()->getInterfaceSize();
    if ( mInterfaceSize != interfaceSize ) {
        setInterfaceSize( interfaceSize );
    }    

    const float w	 = 15.0f;
	Rectf infoRect   = mTrackInfoLabel->getRect();
	
	if( mTrackInfoLabel->isScrollingText() ) {
        mCoverLeftTextureRect->setRect( infoRect.x1, infoRect.y1, infoRect.x1 + w, infoRect.y2 );
    } else {
        mCoverLeftTextureRect->setRect( infoRect.x1, infoRect.y1, infoRect.x1, infoRect.y1 ); // zero size (FIXME: visible true/false? or remove from scene?
    }
    mCoverRightTextureRect->setRect( infoRect.x2 + 1.0f, infoRect.y1, infoRect.x2 - ( w - 1.0f ), infoRect.y2 );
    
}

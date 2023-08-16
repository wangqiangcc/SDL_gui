//
//  GUI_TitleBar.cpp
//  GUI_EditText
//
//  Created by Panutat Tejasen on 18/1/2562 BE.
//  Copyright © 2562 Jimmy Software Co., Ltd. All rights reserved.
//

#include "GUI_TitleBar.h"
extern SDL_Window *GUI_window;

GUI_TitleBar *GUI_TitleBar::create( GUI_View *parent, const char *title,
                               std::function<void(GUI_View*)>callbackFunction ) {
    return new GUI_TitleBar( parent, title, callbackFunction );
}

GUI_TitleBar::GUI_TitleBar(GUI_View *parent, const char *title,
                       std::function<void(GUI_View*)>callbackFunction ) :
    GUI_View( parent, title, 0, 0, -1, GUI_GetAppTopBarHeight()+GUI_GetStatusBarHeight() ),
titleView(NULL)
{
#if defined(__IPHONEOS__)
    setPadding( GUI_GetStatusBarHeight()/GUI_scale, 0, 0, 0 );
#endif
    setCallback(callbackFunction);
    setBackgroundColor(GUI_AppTopBarColor);
    setLayout( GUI_LAYOUT_VERTICAL );
    setBorder( 0 );
    setAlign( GUI_ALIGN_LEFT | GUI_ALIGN_TOP );

    contentView = GUI_View::create(this, "TitleBarContent", 0, 0, -1, GUI_GetAppTopBarHeight());
	contentView->setLayout(GUI_LAYOUT_HORIZONTAL);
	contentView->setMargin(0, 0, 0, 0);
	contentView->setPadding(0, 5, 5, 5);
    contentView->setBorder( 0 );
    contentView->setBackgroundColor( cClear );
    
	imageView = GUI_ImageView::create(contentView, "Icon", "logo.png", 0, 0, 24, 24);
	imageView->setMargin(10, 0, 0, 0);
	//imageView->setPadding(10, 0, 10, 0);

    if( title ) {
        titleView = GUI_Label::create(contentView, title, 30, 0, 0, 0 );
        titleView->setBackgroundColor( cClear );
        titleView->setTextColor(cWhite);
        titleView->setAlign( GUI_ALIGN_LEFT | GUI_ALIGN_VCENTER );

		SDL_SetWindowTitle(GUI_window, title);
    }

	minButton = GUI_Button::create(contentView, NULL, kIcon_solid_window_minimize);
	minButton->setAlign(GUI_ALIGN_RIGHT | GUI_ALIGN_VCENTER);
	minButton->setMargin(0, 0, 0, 0);
	minButton->setCallback([=](GUI_View *bt) {
		SDL_MinimizeWindow(GUI_window);
	});


	maxButton = GUI_Button::create(contentView, NULL, kIcon_solid_window_maximize);
	maxButton->setAlign(GUI_ALIGN_RIGHT | GUI_ALIGN_VCENTER);
	maxButton->setMargin(0, 0, 0, 0);
	maxButton->setCallback([=](GUI_View *bt) {
		if (SDL_GetWindowFlags(GUI_window) & SDL_WINDOW_MAXIMIZED) {
			SDL_RestoreWindow(GUI_window);
		}
		else {
			SDL_MaximizeWindow(GUI_window);
		}
	});

	closeButton = GUI_Button::create(contentView, NULL, kIcon_solid_window_close);
	closeButton->setAlign(GUI_ALIGN_RIGHT | GUI_ALIGN_VCENTER);
	closeButton->setMargin(0, 0, 0, 0);
	closeButton->setCallback([=](GUI_View *bt) {
		SDL_Quit();
	});

}

GUI_TitleBar::~GUI_TitleBar() {
    
}

void GUI_TitleBar::setTitleIcon(const std::string & icon)
{
}

bool GUI_TitleBar::eventHandler(SDL_Event*event) {
    switch (event->type) {
        case GUI_UpdateSize:
        {
            oh = GUI_GetAppTopBarHeight()+GUI_GetStatusBarHeight();
            return GUI_View::eventHandler(event);
        }
        default:
        {
            return GUI_View::eventHandler(event);
        }
    }
    
    return false;
}

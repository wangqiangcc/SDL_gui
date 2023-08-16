//
//  GUI_TopBar.hpp
//  GUI_EditText
//
//  Created by Panutat Tejasen on 18/1/2562 BE.
//  Copyright © 2562 Jimmy Software Co., Ltd. All rights reserved.
//

#ifndef GUI_TitleBar_H
#define GUI_TitleBar_H

#include <stdio.h>
#include <string>
#include "GUI_View.h"
#include "GUI_Label.h"
#include "GUI_ImageView.h"
#include "GUI_Button.h"

class GUI_TitleBar : public GUI_View {
protected:
	GUI_ImageView *imageView;
    GUI_Label *titleView;
	GUI_Button *minButton;
	GUI_Button *maxButton;
	GUI_Button *closeButton;
public:
    static GUI_TitleBar *create( GUI_View *parent, const char *title,
                                std::function<void(GUI_View*)>callbackFunction = NULL );
	GUI_TitleBar(GUI_View *parent, const char *title,
                 std::function<void(GUI_View*)>callbackFunction = NULL );
    virtual ~GUI_TitleBar();
    GUI_View *contentView;

	void setTitleIcon(const std::string& icon);
    
    virtual bool eventHandler(SDL_Event*ev);
};

#endif /* GUI_TitleBar_H */

/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef TSAGE_RINGWORLD2_LOGIC_H
#define TSAGE_RINGWORLD2_LOGIC_H

#include "common/scummsys.h"
#include "tsage/events.h"
#include "tsage/core.h"
#include "tsage/scenes.h"
#include "tsage/globals.h"

namespace TsAGE {

namespace Ringworld2 {

using namespace TsAGE;

#define R2_INVENTORY (*((::TsAGE::Ringworld2::Ringworld2InvObjectList *)g_globals->_inventory))

class SceneFactory {
public:
	static Scene *createScene(int sceneNumber);
};

class SceneArea: public EventHandler {
public:
	Rect _bounds;
	bool _enabled;
	bool _insideArea;
	CursorType _cursorNum;
	CursorType _savedCursorNum;
	int _cursorState;
public:
	SceneArea();
	void setDetails(const Rect &bounds, CursorType cursor);

	virtual void synchronize(Serializer &s);
	virtual void remove();
	virtual void process(Event &event);
};

class SceneExit: public SceneArea {
public:
	bool _moving;
	int _sceneNumber;
	Common::Point _destPos;
public:
	SceneExit();
	virtual void setDetails(const Rect &bounds, CursorType cursor, int sceneNumber);
	virtual void setDest(const Common::Point &p) { _destPos = p; }
	virtual void changeScene();

	virtual void synchronize(Serializer &s);
	virtual void process(Event &event);
};

class SceneExt: public Scene {
private:
	static void startStrip();
	static void endStrip();
public:
	byte _field312[256];
	int _field372;
	bool _savedPlayerEnabled;
	bool _savedUiEnabled;
	bool _savedCanWalk;
	int _field37A;

	SceneObject *_focusObject;
	Visage _cursorVisage;
	SynchronizedList<SceneArea *> _sceneAreas;

	Rect _v51C34;
public:
	SceneExt();

	virtual Common::String getClassName() { return "SceneExt"; }
	virtual void postInit(SceneObjectList *OwnerList = NULL);
	virtual void remove();
	virtual void process(Event &event);
	virtual void dispatch();
	virtual void loadScene(int sceneNum);
	virtual void refreshBackground(int xAmount, int yAmount);
	virtual void saveCharacter(int characterIndex);
	virtual void restore() {}

	bool display(CursorType action, Event &event);
	void fadeOut();
	void clearScreen();
	void scalePalette(int RFactor, int GFactor, int BFactor);
};

class SceneHandlerExt: public SceneHandler {
public:
	virtual void postInit(SceneObjectList *OwnerList = NULL);
	virtual void process(Event &event);

	void setupPaletteMaps();
};


class DisplayHotspot : public SceneObject {
private:
	Common::Array<int> _actions;
	bool performAction(int action);
public:
	DisplayHotspot(int regionId, ...);

	virtual void doAction(int action) {
		if (!performAction(action))
			SceneHotspot::doAction(action);
	}
};

class DisplayObject : public SceneObject {
private:
	Common::Array<int> _actions;
	bool performAction(int action);
public:
	DisplayObject(int firstAction, ...);

	virtual void doAction(int action) {
		if (!performAction(action))
			SceneHotspot::doAction(action);
	}
};

class SceneObjectExt : public SceneObject {
public:
	int _state;

	virtual void synchronize(Serializer &s) {
		SceneObject::synchronize(s);
		s.syncAsSint16LE(_state);
	}
	virtual Common::String getClassName() { return "SceneObjectExt"; }
};

/*--------------------------------------------------------------------------*/

class Ringworld2InvObjectList : public InvObjectList {
public:
	InvObject _none;
	InvObject _inv1;
	InvObject _inv2;
	InvObject _negatorGun;
	InvObject _steppingDisks;
	InvObject _inv5;
	InvObject _inv6;
	InvObject _inv7;
	InvObject _inv8;
	InvObject _inv9;
	InvObject _inv10;
	InvObject _inv11;
	InvObject _inv12;
	InvObject _inv13;
	InvObject _inv14;
	InvObject _inv15;
	InvObject _inv16;
	InvObject _inv17;
	InvObject _inv18;
	InvObject _inv19;
	InvObject _inv20;
	InvObject _inv21;
	InvObject _inv22;
	InvObject _inv23;
	InvObject _inv24;
	InvObject _inv25;
	InvObject _inv26;
	InvObject _inv27;
	InvObject _inv28;
	InvObject _inv29;
	InvObject _inv30;
	InvObject _inv31;
	InvObject _inv32;
	InvObject _inv33;
	InvObject _inv34;
	InvObject _inv35;
	InvObject _inv36;
	InvObject _inv37;
	InvObject _inv38;
	InvObject _inv39;
	InvObject _inv40;
	InvObject _inv41;
	InvObject _inv42;
	InvObject _inv43;
	InvObject _inv44;
	InvObject _inv45;
	InvObject _inv46;
	InvObject _inv47;
	InvObject _inv48;
	InvObject _inv49;
	InvObject _inv50;
	InvObject _inv51;
	InvObject _inv52;

	Ringworld2InvObjectList();
	void reset();
	void setObjectScene(int objectNum, int sceneNumber);

	virtual Common::String getClassName() { return "Ringworld2InvObjectList"; }
};

#define RING2_INVENTORY (*((::TsAGE::Ringworld2::Ringworld2InvObjectList *)g_globals->_inventory))

class Ringworld2Game: public Game {
public:
	virtual void start();
	virtual void restart();
	virtual void endGame(int resNum, int lineNum);

	virtual Scene *createScene(int sceneNumber);
	virtual void processEvent(Event &event);
	virtual void rightClick();
	virtual bool canSaveGameStateCurrently();
	virtual bool canLoadGameStateCurrently();
};

class NamedHotspot : public SceneHotspot {
public:
	NamedHotspot();

	virtual bool startAction(CursorType action, Event &event);
	virtual Common::String getClassName() { return "NamedHotspot"; }
};

class NamedHotspotExt : public NamedHotspot {
public:
	int _flag;
	NamedHotspotExt() { _flag = 0; }

	virtual Common::String getClassName() { return "NamedHotspot"; }
	virtual void synchronize(Serializer &s) {
		NamedHotspot::synchronize(s);
		s.syncAsSint16LE(_flag);
	}
};

class SceneActor: public SceneObject {
public:
	virtual Common::String getClassName() { return "SceneActor"; }
	virtual void postInit(SceneObjectList *OwnerList = NULL);
	virtual bool startAction(CursorType action, Event &event);
};

class SceneActorExt: public SceneActor {
public:
	int _state;

	SceneActorExt() { _state = 0; }

	virtual Common::String getClassName() { return "SceneActorExt"; }
	virtual void synchronize(Serializer &s) {
		SceneActor::synchronize(s);
		s.syncAsSint16LE(_state);
	}
};

class SceneAreaObject: public SceneArea {
	class Object1: public SceneActor {
	public:
	};
public:
	Object1 _object1;
	int _insetCount;

	virtual void remove();
	virtual void process(Event &event);
	void setDetails(int visage, int strip, int frameNumber, const Common::Point &pt);
	void setDetails(int resNum, int lookLineNum, int talkLineNum, int useLineNum);
};

class UnkObject1200 : public SavedObject {
public:
	Rect _rect1;
	Rect _rect2;

	int *_field16;
	int *_field3A;

	int _field12;
	int _field14;
	int _field26;
	int _field28;
	int _field2A;
	int _field2C;
	int _field2E;
	int _field30;
	int _field32;
	int _field34;
	int _field36;
	int _field38;
	int _field3E;
	int _field40;

	UnkObject1200();
	void synchronize(Serializer &s);

	void sub51AE9(int arg1);
	int sub51AF8(Common::Point pt);
	bool sub51AFD(Common::Point pt);
	void sub51B02();
	void sub9EDE8(Rect rect);
	int sub9EE22(int &arg1, int &arg2);
	virtual Common::String getClassName() { return "UnkObject1200"; }
};

class AnimationPlayer: public EventHandler {
public:
	Common::File _resourceFile;
	void *_fieldA;
	void *_field16;

	byte *_dataP;
	Rect _rect1, _screenBounds;
	int _field38;
	int _field3A, _field3C;
	int _field56;
	int _field58, _field5A;
	ScenePalette _palette;
	byte _palData[256 * 3];
	Action *_endAction;
	int _field576;
	int _field57C;
	int _palStart, _palSize;
	int _field904;
	int _field908;
	int _field90C;
	int _field90E;
	uint _field910;
	uint32 _gameFrame;
public:
	AnimationPlayer();
	~AnimationPlayer();

	virtual void synchronize(Serializer &s);
	virtual void remove();
	virtual void process(Event &event);
	virtual void dispatch();
	virtual void flipPane() {}
	virtual void changePane() {}
	virtual void proc14() {}

	bool load(int rlbNum, Action *endAction = NULL);
	void drawFrame(int frameIndex);
	void method2();
	bool method3();
	void method4();
	void method5() {}
};

class AnimationPlayerExt: public AnimationPlayer {
public:
	int _v;
public:
	AnimationPlayerExt();

	virtual void synchronize(Serializer &s);
};

} // End of namespace Ringworld2

} // End of namespace TsAGE

#endif

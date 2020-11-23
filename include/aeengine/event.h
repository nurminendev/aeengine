/*
 *  AE Engine
 *
 *  Copyright (C) 2003 Riku "Rakkis" Nurminen
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef __AELIB_AEENGINE_EVENT_H__
#define __AELIB_AEENGINE_EVENT_H__

#include <aedefs.h>

/** @defgroup eventstructs AE event structs and definitions.
 * AE event structures and definitions.
 * @{
 */

/// Key definition table.
/*!
  This is essentially the same as SDLKEY_*, the only
  change is in the name (AEKEY_*).
*/
enum aeKey {
	AEKEY_UNKNOWN	= 0,
	AEKEY_FIRST		= 0,
	AEKEY_BACKSPACE	= 8,
	AEKEY_TAB		= 9,
	AEKEY_CLEAR		= 12,
	AEKEY_RETURN		= 13,
	AEKEY_PAUSE		= 19,
	AEKEY_ESCAPE		= 27,
	AEKEY_SPACE		= 32,
	AEKEY_EXCLAIM	= 33,
	AEKEY_QUOTEDBL	= 34,
	AEKEY_HASH		= 35,
	AEKEY_DOLLAR		= 36,
	AEKEY_AMPERSAND	= 38,
	AEKEY_QUOTE		= 39,
	AEKEY_LEFTPAREN	= 40,
	AEKEY_RIGHTPAREN	= 41,
	AEKEY_ASTERISK	= 42,
	AEKEY_PLUS		= 43,
	AEKEY_COMMA		= 44,
	AEKEY_MINUS		= 45,
	AEKEY_PERIOD		= 46,
	AEKEY_SLASH		= 47,
	AEKEY_0			= 48,
	AEKEY_1			= 49,
	AEKEY_2			= 50,
	AEKEY_3			= 51,
	AEKEY_4			= 52,
	AEKEY_5			= 53,
	AEKEY_6			= 54,
	AEKEY_7			= 55,
	AEKEY_8			= 56,
	AEKEY_9			= 57,
	AEKEY_COLON		= 58,
	AEKEY_SEMICOLON	= 59,
	AEKEY_LESS		= 60,
	AEKEY_EQUALS		= 61,
	AEKEY_GREATER	= 62,
	AEKEY_QUESTION	= 63,
	AEKEY_AT			= 64,

	AEKEY_LEFTBRACKET	= 91,
	AEKEY_BACKSLASH	= 92,
	AEKEY_RIGHTBRACKET	= 93,
	AEKEY_CARET		= 94,
	AEKEY_UNDERSCORE	= 95,
	AEKEY_BACKQUOTE	= 96,
	AEKEY_a			= 97,
	AEKEY_b			= 98,
	AEKEY_c			= 99,
	AEKEY_d			= 100,
	AEKEY_e			= 101,
	AEKEY_f			= 102,
	AEKEY_g			= 103,
	AEKEY_h			= 104,
	AEKEY_i			= 105,
	AEKEY_j			= 106,
	AEKEY_k			= 107,
	AEKEY_l			= 108,
	AEKEY_m			= 109,
	AEKEY_n			= 110,
	AEKEY_o			= 111,
	AEKEY_p			= 112,
	AEKEY_q			= 113,
	AEKEY_r			= 114,
	AEKEY_s			= 115,
	AEKEY_t			= 116,
	AEKEY_u			= 117,
	AEKEY_v			= 118,
	AEKEY_w			= 119,
	AEKEY_x			= 120,
	AEKEY_y			= 121,
	AEKEY_z			= 122,
	AEKEY_DELETE		= 127,

	AEKEY_WORLD_0	= 160,
	AEKEY_WORLD_1	= 161,
	AEKEY_WORLD_2	= 162,
	AEKEY_WORLD_3	= 163,
	AEKEY_WORLD_4	= 164,
	AEKEY_WORLD_5	= 165,
	AEKEY_WORLD_6	= 166,
	AEKEY_WORLD_7	= 167,
	AEKEY_WORLD_8	= 168,
	AEKEY_WORLD_9	= 169,
	AEKEY_WORLD_10	= 170,
	AEKEY_WORLD_11	= 171,
	AEKEY_WORLD_12	= 172,
	AEKEY_WORLD_13	= 173,
	AEKEY_WORLD_14	= 174,
	AEKEY_WORLD_15	= 175,
	AEKEY_WORLD_16	= 176,
	AEKEY_WORLD_17	= 177,
	AEKEY_WORLD_18	= 178,
	AEKEY_WORLD_19	= 179,
	AEKEY_WORLD_20	= 180,
	AEKEY_WORLD_21	= 181,
	AEKEY_WORLD_22	= 182,
	AEKEY_WORLD_23	= 183,
	AEKEY_WORLD_24	= 184,
	AEKEY_WORLD_25	= 185,
	AEKEY_WORLD_26	= 186,
	AEKEY_WORLD_27	= 187,
	AEKEY_WORLD_28	= 188,
	AEKEY_WORLD_29	= 189,
	AEKEY_WORLD_30	= 190,
	AEKEY_WORLD_31	= 191,
	AEKEY_WORLD_32	= 192,
	AEKEY_WORLD_33	= 193,
	AEKEY_WORLD_34	= 194,
	AEKEY_WORLD_35	= 195,
	AEKEY_WORLD_36	= 196,
	AEKEY_WORLD_37	= 197,
	AEKEY_WORLD_38	= 198,
	AEKEY_WORLD_39	= 199,
	AEKEY_WORLD_40	= 200,
	AEKEY_WORLD_41	= 201,
	AEKEY_WORLD_42	= 202,
	AEKEY_WORLD_43	= 203,
	AEKEY_WORLD_44	= 204,
	AEKEY_WORLD_45	= 205,
	AEKEY_WORLD_46	= 206,
	AEKEY_WORLD_47	= 207,
	AEKEY_WORLD_48	= 208,
	AEKEY_WORLD_49	= 209,
	AEKEY_WORLD_50	= 210,
	AEKEY_WORLD_51	= 211,
	AEKEY_WORLD_52	= 212,
	AEKEY_WORLD_53	= 213,
	AEKEY_WORLD_54	= 214,
	AEKEY_WORLD_55	= 215,
	AEKEY_WORLD_56	= 216,
	AEKEY_WORLD_57	= 217,
	AEKEY_WORLD_58	= 218,
	AEKEY_WORLD_59	= 219,
	AEKEY_WORLD_60	= 220,
	AEKEY_WORLD_61	= 221,
	AEKEY_WORLD_62	= 222,
	AEKEY_WORLD_63	= 223,
	AEKEY_WORLD_64	= 224,
	AEKEY_WORLD_65	= 225,
	AEKEY_WORLD_66	= 226,
	AEKEY_WORLD_67	= 227,
	AEKEY_WORLD_68	= 228,
	AEKEY_WORLD_69	= 229,
	AEKEY_WORLD_70	= 230,
	AEKEY_WORLD_71	= 231,
	AEKEY_WORLD_72	= 232,
	AEKEY_WORLD_73	= 233,
	AEKEY_WORLD_74	= 234,
	AEKEY_WORLD_75	= 235,
	AEKEY_WORLD_76	= 236,
	AEKEY_WORLD_77	= 237,
	AEKEY_WORLD_78	= 238,
	AEKEY_WORLD_79	= 239,
	AEKEY_WORLD_80	= 240,
	AEKEY_WORLD_81	= 241,
	AEKEY_WORLD_82	= 242,
	AEKEY_WORLD_83	= 243,
	AEKEY_WORLD_84	= 244,
	AEKEY_WORLD_85	= 245,
	AEKEY_WORLD_86	= 246,
	AEKEY_WORLD_87	= 247,
	AEKEY_WORLD_88	= 248,
	AEKEY_WORLD_89	= 249,
	AEKEY_WORLD_90	= 250,
	AEKEY_WORLD_91	= 251,
	AEKEY_WORLD_92	= 252,
	AEKEY_WORLD_93	= 253,
	AEKEY_WORLD_94	= 254,
	AEKEY_WORLD_95	= 255,

	AEKEY_KP0		= 256,
	AEKEY_KP1		= 257,
	AEKEY_KP2		= 258,
	AEKEY_KP3		= 259,
	AEKEY_KP4		= 260,
	AEKEY_KP5		= 261,
	AEKEY_KP6		= 262,
	AEKEY_KP7		= 263,
	AEKEY_KP8		= 264,
	AEKEY_KP9		= 265,
	AEKEY_KP_PERIOD	= 266,
	AEKEY_KP_DIVIDE	= 267,
	AEKEY_KP_MULTIPLY	= 268,
	AEKEY_KP_MINUS	= 269,
	AEKEY_KP_PLUS	= 270,
	AEKEY_KP_ENTER	= 271,
	AEKEY_KP_EQUALS	= 272,

	AEKEY_UP			= 273,
	AEKEY_DOWN		= 274,
	AEKEY_RIGHT		= 275,
	AEKEY_LEFT		= 276,
	AEKEY_INSERT		= 277,
	AEKEY_HOME		= 278,
	AEKEY_END		= 279,
	AEKEY_PAGEUP		= 280,
	AEKEY_PAGEDOWN	= 281,

	AEKEY_F1			= 282,
	AEKEY_F2			= 283,
	AEKEY_F3			= 284,
	AEKEY_F4			= 285,
	AEKEY_F5			= 286,
	AEKEY_F6			= 287,
	AEKEY_F7			= 288,
	AEKEY_F8			= 289,
	AEKEY_F9			= 290,
	AEKEY_F10		= 291,
	AEKEY_F11		= 292,
	AEKEY_F12		= 293,
	AEKEY_F13		= 294,
	AEKEY_F14		= 295,
	AEKEY_F15		= 296,

	AEKEY_NUMLOCK	= 300,
	AEKEY_CAPSLOCK	= 301,
	AEKEY_SCROLLOCK	= 302,
	AEKEY_RSHIFT		= 303,
	AEKEY_LSHIFT		= 304,
	AEKEY_RCTRL		= 305,
	AEKEY_LCTRL		= 306,
	AEKEY_RALT		= 307,
	AEKEY_LALT		= 308,
	AEKEY_RMETA		= 309,
	AEKEY_LMETA		= 310,
	AEKEY_LSUPER		= 311,
	AEKEY_RSUPER		= 312,
	AEKEY_MODE		= 313,
	AEKEY_COMPOSE	= 314,

	AEKEY_HELP		= 315,
	AEKEY_PRINT		= 316,
	AEKEY_SYSREQ		= 317,
	AEKEY_BREAK		= 318,
	AEKEY_MENU		= 319,
	AEKEY_POWER		= 320,
	AEKEY_EURO		= 321,
	AEKEY_UNDO		= 322,

	AEKEY_LAST
};

/// Just a rename...
typedef SDLMod aeKeyMod;

/// Event type codes. Used to indentify the type of an event occuring.
enum aeEventType {
	aeevActiveEvent,
	aeevBroadcast,
	aeevKeyDown,
	aeevKeyUp,
	aeevMouseMotion,
	aeevMouseButtonDown,
	aeevMouseButtonUp,
	aeevQuit
};

/// Event command codes.
enum aeEventCmdCode {
	aecmdPreFrame,
	aecmdProcessFrame,
	aecmdPostFrame,
	aecmdToggleFullscreen
};

/// Application focus states.
enum aeAppActiveState {
	aeAppMouseFocus,
	aeAppInputFocus,
	aeAppActive
};

/// Button states for press/release.
enum aeButtonState {
	aePressed,
	aeReleased
};

/// Mouse button definitions.
enum aeMouseButton {
	aeButtonLeft = 1,
	aeButtonMiddle = 2,
	aeButtonRight = 3
};

/// Mouse button states for press/release.
enum aeMouseButtonState {
	aeNonePressed = 0,
	aeLeftPressed = 1,
	aeMiddlePressed = 2,
	aeRightPressed = 3
};

/** 
 * Holds info for app focus gain/lost event.
 * 
 */
struct aeActiveEvent {
	/// Event type.
	aeEventType type;
	/// Whether it was gain or loss. 0 = loss, 1 = gain.
	uint8 gain;
	/// App focus state.
	aeAppActiveState state;
};

/** 
 * Event command struct.
 * 
 */
struct aeEventCommand {
	/// Event command code.
	aeEventCmdCode code;
};

/** 
 * Key press info.
 * 
 */
struct aeKeySym {
	/// Scancode.
	uint8 scancode;
	/// The key this event occured on.
	aeKey sym;
	/// Modified key.
	aeKeyMod mod;
	/// Unicode.
	uint16 unicode;
};

/** 
 * Keyboard event struct.
 * 
 */
struct aeKeyboardEvent {
	/// Event type.
	aeEventType type;
	/// Button state.
	aeButtonState state;
	// Key press information.
	aeKeySym keysym;
};

/** 
 * Mouse motion event struct.
 * 
 */
struct aeMouseMotionEvent {
	/// Event type.
	aeEventType type;
	/// Mouse button state.
	aeMouseButtonState state;
	/// X and Y pos of the mouse cursor.
	uint16 x, y;
	/// The change in mouse X and Y from the last position.
	sint16 xrel, yrel;
};

/** 
 * Mouse button event struct.
 * 
 */
struct aeMouseButtonEvent {
	/// Event type.
	aeEventType type;
	/// Mouse button this even occured on.
	aeMouseButton button;
	/// Button state.
	aeButtonState state;
	/// Mouse position.
	uint16 x, y;
};

/** 
 * Quit event. Used on application quit.
 * 
 */
struct aeQuitEvent {
	/// Event type.
	aeEventType type;
};

/** 
 * The AE event structure.
 * 
 */
struct aeEvent {
	/// Event type.
	aeEventType type;
	/// Event command.
	aeEventCommand cmd;
	/// Active event.
	aeActiveEvent active;
	/// Keyboard event.
	aeKeyboardEvent key;
	/// Mouse motion event.
	aeMouseMotionEvent motion;
	/// Mouse button event.
	aeMouseButtonEvent button;
	/// Quit event.
	aeQuitEvent quit;
};

/// Typedef for a event handler callback variable.
typedef bool (*aeEventHandlerCallback)(aeEvent &);

/** @} */

#endif // __AELIB_AEENGINE_EVENT_H__

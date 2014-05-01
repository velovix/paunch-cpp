#ifndef PAUNCH_H_
#define PAUNCH_H_

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <cmath>

namespace paunch {

// Plane Constants
const int X = 1;
const int Y = 2;

// Directional Constants
const int Up    = 1;
const int Down  = 2;
const int Left  = 3;
const int Right = 4;

// Button State Constants
const int Press   = GLFW_PRESS;
const int Release = GLFW_RELEASE;
const int Hold    = GLFW_REPEAT;

// Mouse Button ID Constants
const int MouseButton1      = GLFW_MOUSE_BUTTON_1;
const int MouseButton2      = GLFW_MOUSE_BUTTON_2;
const int MouseButton3      = GLFW_MOUSE_BUTTON_3;
const int MouseButton4      = GLFW_MOUSE_BUTTON_4;
const int MouseButton5      = GLFW_MOUSE_BUTTON_5;
const int MouseButton6      = GLFW_MOUSE_BUTTON_6;
const int MouseButton7      = GLFW_MOUSE_BUTTON_7;
const int MouseButton8      = GLFW_MOUSE_BUTTON_8;
const int MouseButtonLast   = GLFW_MOUSE_BUTTON_LAST;
const int MouseButtonLeft   = GLFW_MOUSE_BUTTON_LEFT;
const int MouseButtonRight  = GLFW_MOUSE_BUTTON_RIGHT;
const int MouseButtonMiddle = GLFW_MOUSE_BUTTON_MIDDLE;

// Keyboard Key ID Constants
const int KeyUnknown      = GLFW_KEY_UNKNOWN;
const int KeySpace        = GLFW_KEY_SPACE;
const int KeyApostrophe   = GLFW_KEY_APOSTROPHE;
const int KeyComma        = GLFW_KEY_COMMA;
const int KeyMinus        = GLFW_KEY_MINUS;
const int KeyPeriod       = GLFW_KEY_PERIOD;
const int KeySlash        = GLFW_KEY_SLASH;
const int Key0            = GLFW_KEY_0;
const int Key1            = GLFW_KEY_1;
const int Key2            = GLFW_KEY_2;
const int Key3            = GLFW_KEY_3;
const int Key4            = GLFW_KEY_4;
const int Key5            = GLFW_KEY_5;
const int Key6            = GLFW_KEY_6;
const int Key7            = GLFW_KEY_7;
const int Key8            = GLFW_KEY_8;
const int Key9            = GLFW_KEY_9;
const int KeySemicolon    = GLFW_KEY_SEMICOLON;
const int KeyEqual        = GLFW_KEY_EQUAL;
const int KeyA            = GLFW_KEY_A;
const int KeyB            = GLFW_KEY_B;
const int KeyC            = GLFW_KEY_C;
const int KeyD            = GLFW_KEY_D;
const int KeyE            = GLFW_KEY_E;
const int KeyF            = GLFW_KEY_F;
const int KeyG            = GLFW_KEY_G;
const int KeyH            = GLFW_KEY_H;
const int KeyI            = GLFW_KEY_I;
const int KeyJ            = GLFW_KEY_J;
const int KeyK            = GLFW_KEY_K;
const int KeyL            = GLFW_KEY_L;
const int KeyM            = GLFW_KEY_M;
const int KeyN            = GLFW_KEY_N;
const int KeyO            = GLFW_KEY_O;
const int KeyP            = GLFW_KEY_P;
const int KeyQ            = GLFW_KEY_Q;
const int KeyR            = GLFW_KEY_R;
const int KeyS            = GLFW_KEY_S;
const int KeyT            = GLFW_KEY_T;
const int KeyU            = GLFW_KEY_U;
const int KeyV            = GLFW_KEY_V;
const int KeyW            = GLFW_KEY_W;
const int KeyX            = GLFW_KEY_X;
const int KeyY            = GLFW_KEY_Y;
const int KeyZ            = GLFW_KEY_Z;
const int KeyLeftBracket  = GLFW_KEY_LEFT_BRACKET;
const int KeyBackslash    = GLFW_KEY_BACKSLASH;
const int KeyRightBracket = GLFW_KEY_RIGHT_BRACKET;
const int KeyGraveAccent  = GLFW_KEY_GRAVE_ACCENT;
const int KeyWorld1       = GLFW_KEY_WORLD_1;
const int KeyWorld2       = GLFW_KEY_WORLD_2;
const int KeyEscape       = GLFW_KEY_ESCAPE;
const int KeyEnter        = GLFW_KEY_ENTER;
const int KeyTab          = GLFW_KEY_TAB;
const int KeyBackspace    = GLFW_KEY_BACKSPACE;
const int KeyInsert       = GLFW_KEY_INSERT;
const int KeyDelete       = GLFW_KEY_DELETE;
const int KeyRight        = GLFW_KEY_RIGHT;
const int KeyLeft         = GLFW_KEY_LEFT;
const int KeyDown         = GLFW_KEY_DOWN;
const int KeyUp           = GLFW_KEY_UP;
const int KeyPageUp       = GLFW_KEY_PAGE_UP;
const int KeyPageDown     = GLFW_KEY_PAGE_DOWN;
const int KeyHome         = GLFW_KEY_HOME;
const int KeyEnd          = GLFW_KEY_END;
const int KeyCapsLock     = GLFW_KEY_CAPS_LOCK;
const int KeyScrollLock   = GLFW_KEY_SCROLL_LOCK;
const int KeyNumLock      = GLFW_KEY_NUM_LOCK;
const int KeyPrintScreen  = GLFW_KEY_PRINT_SCREEN;
const int KeyPause        = GLFW_KEY_PAUSE;
const int KeyF1           = GLFW_KEY_F1;
const int KeyF2           = GLFW_KEY_F2;
const int KeyF3           = GLFW_KEY_F3;
const int KeyF4           = GLFW_KEY_F4;
const int KeyF5           = GLFW_KEY_F5;
const int KeyF6           = GLFW_KEY_F6;
const int KeyF7           = GLFW_KEY_F7;
const int KeyF8           = GLFW_KEY_F8;
const int KeyF9           = GLFW_KEY_F9;
const int KeyF10          = GLFW_KEY_F10;
const int KeyF11          = GLFW_KEY_F11;
const int KeyF12          = GLFW_KEY_F12;
const int KeyF13          = GLFW_KEY_F13;
const int KeyF14          = GLFW_KEY_F14;
const int KeyF15          = GLFW_KEY_F15;
const int KeyF16          = GLFW_KEY_F16;
const int KeyF17          = GLFW_KEY_F17;
const int KeyF18          = GLFW_KEY_F18;
const int KeyF19          = GLFW_KEY_F19;
const int KeyF20          = GLFW_KEY_F20;
const int KeyF21          = GLFW_KEY_F21;
const int KeyF22          = GLFW_KEY_F22;
const int KeyF23          = GLFW_KEY_F23;
const int KeyF24          = GLFW_KEY_F24;
const int KeyF25          = GLFW_KEY_F25;
const int KeyKp0          = GLFW_KEY_KP_0;
const int KeyKp1          = GLFW_KEY_KP_1;
const int KeyKp2          = GLFW_KEY_KP_2;
const int KeyKp3          = GLFW_KEY_KP_3;
const int KeyKp4          = GLFW_KEY_KP_4;
const int KeyKp5          = GLFW_KEY_KP_5;
const int KeyKp6          = GLFW_KEY_KP_6;
const int KeyKp7          = GLFW_KEY_KP_7;
const int KeyKp8          = GLFW_KEY_KP_8;
const int KeyKp9          = GLFW_KEY_KP_9;
const int KeyKpDecimal    = GLFW_KEY_KP_DECIMAL;
const int KeyKpDivide     = GLFW_KEY_KP_DIVIDE;
const int KeyKpMultiply   = GLFW_KEY_KP_MULTIPLY;
const int KeyKpSubtract   = GLFW_KEY_KP_SUBTRACT;
const int KeyKpAdd        = GLFW_KEY_KP_ADD;
const int KeyKpEnter      = GLFW_KEY_KP_ENTER;
const int KeyKpEqual      = GLFW_KEY_KP_EQUAL;
const int KeyLeftShift    = GLFW_KEY_LEFT_SHIFT;
const int KeyLeftControl  = GLFW_KEY_LEFT_CONTROL;
const int KeyLeftAlt      = GLFW_KEY_LEFT_ALT;
const int KeyLeftSuper    = GLFW_KEY_LEFT_SUPER;
const int KeyRightShift   = GLFW_KEY_RIGHT_SHIFT;
const int KeyRightControl = GLFW_KEY_RIGHT_CONTROL;
const int KeyRightAlt     = GLFW_KEY_RIGHT_ALT;
const int KeyRightSuper   = GLFW_KEY_RIGHT_SUPER;
const int KeyMenu         = GLFW_KEY_MENU;
const int KeyLast         = GLFW_KEY_LAST;

// Shader Type Constants
const int Vertex   = GL_VERTEX_SHADER;
const int Fragment = GL_FRAGMENT_SHADER;

// Vertex Interpretation Constants
const GLuint Points        = GL_POINTS;
const GLuint LineStrip     = GL_LINE_STRIP;
const GLuint LineLoop      = GL_LINE_LOOP;
const GLuint Lines         = GL_LINES;
const GLuint TriangleStrip = GL_TRIANGLE_STRIP;
const GLuint TriangleFan   = GL_TRIANGLE_FAN;
const GLuint Triangles     = GL_TRIANGLES;

// Sound State Constants
const int Initial = AL_INITIAL;
const int Playing = AL_PLAYING;
const int Paused  = AL_PAUSED;
const int Stopped = AL_STOPPED;

/* class Error
 * Error defines the exception type that is thrown by Paunch-specific
 * functionalities.
 *
 * Methods:
 * Error(std::string message)
 * * Creates a new Error object with the given message.
 * std::string Report()
 * * Returns a string describing the error.
 */
class Error {
	std::string message;

public:
	Error(std::string message);
	std::string Report();
};

/* class Int2
 * Int2 represents two integer values.
 *
 * Variables:
 * int x
 * * The first integer value.
 * int y
 * * The second integer value.
 *
 * Methods:
 * Int2()
 * * Creates an Int2 with two zero values.
 * Int2(int x, int y)
 * * Creates an Int2 with the supplied values.
 */
class Int2 {
public:
	int x;
	int y;
	Int2() : x(0), y(0) {};
	Int2(int x, int y) : x(x), y(y) {};
};

/* class Double2
 * Double2 represents two double (64-bit floating point) values.
 *
 * Variables:
 * double x
 * * The first double value.
 * double y
 * * The second double value.
 *
 * Methods:
 * Double2()
 * * Creates a Double2 with two zero values.
 * Double2(double x, double y)
 * * Creates a Double2 with the supplied values.
 */
class Double2 {
public:
	double x;
	double y;
	Double2() {};
	Double2(double x, double y) : x(x), y(y) {};
};

class Point;
class Bounding;
class Line;
class Polygon;

/* class Collider
 * Collider is a virtual class representing an object that can be tested
 * against other objects for a collision.
 *
 * Methods:
 * bool Collides(Collider &collider)
 * * Tests for a collision between the Collider object and the supplied
 * * Collider object.
 * Double2 DistanceToTangentPoint(Point &point, int side)
 * * Returns the distance to a point on the edge of the Collision object. The
 * * edge it uses is specified by the side argument, which may be the constants
 * * Up, Down, Left, or Right.
 */
class Collider {
	friend class Point;
	friend class Bounding;
	friend class Line;
	friend class Polygon;
	virtual bool Collides(Point &point) = 0;
	virtual bool Collides(Bounding &bounding) = 0;
	virtual bool Collides(Line &line) = 0;
	virtual bool Collides(Polygon &polygon) = 0;
public:
	virtual bool Collides(Collider &collider) = 0;
	virtual Double2 DistanceToTangentPoint(Point &point, int side) = 0;
};

/* class Mover
 * Mover is a virtual class representing an object that has a position on the
 * coordinate plane and can be moved from that position.
 *
 * Methods:
 * void Move(double x, double y)
 * * Moves the Mover object the specified x and y distance.
 * void SetPosition(double x, double y)
 * * Sets the position of the Mover object to the specified position.
 * Double2 GetPosition()
 * * Returns a Double2 representing the position of the Mover object.
 */
class Mover {
public:
	virtual void Move(double x, double y) =0;
	virtual void SetPosition(double x, double y) =0;
	virtual Double2 GetPosition() =0;
};

/* class Point
 * Point is a single geometric point on a coordinate plane. It inherits the
 * virtual classes Mover and Collider.
 *
 * Variables:
 * double x
 * * The x position of the Point object. 
 * double y
 * * The y position of the Point object.
 * 
 * Methods:
 * Point()
 * * Creates a Point object at (0, 0).
 * Point(double x, double y)
 * * Creates a Point object at the specified location.
 * bool Collides(Collider &collider)
 * * Redefined from the virtual class Collider. Tests for a collision between
 * * the Point object and the Collider object.
 * void Move(double x, double y)
 * * Redefined from the virtual class Mover. Moves the Point object the
 * * specified distance.
 * void SetPosition(double x, double y)
 * * Redefined from the virtual class Mover. Sets the position of the Point
 * * object to the specified position.
 * Double2 GetPosition()
 * * Redefined from the virtual class Mover. Returns a Double2 representing the
 * * position of the Point object.
 * Double2 DistanceToTangentPoint(Point &point, int side)
 * * Redefined from the virtual class Mover. Always returns the distance from
 * * the specified Point object to the Point object itself.
 */
class Point: public Mover, public Collider {
	friend class Bounding;
	friend class Line;
	friend class Polygon;
	bool Collides(Point &point);
	bool Collides(Bounding &bounding);
	bool Collides(Line &line);
	bool Collides(Polygon &polygon);
public:
	double x;
	double y;

	Point();
	Point(double x, double y);

	bool Collides(Collider &collider);

	void Move(double x, double y);
	void SetPosition(double x, double y);
	Double2 GetPosition();
	Double2 DistanceToTangentPoint(Point &point, int side);
};

/* class Bounding
 * Bounding is a bounding box. More simply stated, it's a rectangle.
 *
 * Variables:
 * Point start
 * * The bottom-left point of the Bounding object.
 * Point end
 * * The top-right point of the Bounding object.
 * 
 * Methods:
 * Bounding()
 * * Creates a Bounding object that starts and ends at (0,0).
 * Bounding(Point start, Point end)
 * * Creates a Bounding object using the supplied Point objects as hints. The
 * * start and end points of the Bounding will always be the bottom-left and
 * * top-right points respectively, regardless of the values given to this
 * * method.
 * bool Collides(Collider &collider)
 * * Redefined from the virtual class Collider. Tests for a collision between
 * * the Bounding object and the Collider object.
 * void Move(double x, double y)
 * * Redefined from the virtual class Mover. Moves the Bounding object the
 * * specified distance.
 * void SetPosition(double x, double y)
 * * Redefined from the virtual class Mover. Sets the position of the Bounding
 * * object to the specified position, relative to the bottom-left point.
 * Double2 GetPosition()
 * * Redefined from the virtual class Mover. Returns a Double2 representing the
 * * bottom-left point of the Bounding object.
 * Double2 DistanceToTangentPoint(Point &point, int side)
 * * Redefined from the virtual class Mover. Returns the distance from the
 * * given Point object to a point on the given side. If Up or Down is
 * * specified, this method will attempt to find a tangent point at the same x
 * * position as the specified Point object. If Left or Right is specified,
 * * this method will attempt to find a tangent point at the same y position as
 * * the specified Point object.
 */
class Bounding: public Mover, public Collider {
	friend class Point;
	friend class Line;
	friend class Polygon;
	bool Collides(Point &point);
	bool Collides(Bounding &bounding);
	bool Collides(Line &line);
	bool Collides(Polygon &polygon);
public:
	Point start;
	Point end;

	Bounding();
	Bounding(Point start, Point end);

	bool Collides(Collider &collider);

	void Move(double x, double y);
	void SetPosition(double x, double y);
	Double2 GetPosition();
	Double2 DistanceToTangentPoint(Point &point, int side);
};

/* class Line
 * Line is the line segment created by two Point objects.
 *
 * Variables:
 * Point start
 * * The left-most point on the Line object, if one exists. Otherwise, it's the
 * * first Point object given to Line(Point start, Point end).
 * Point end
 * * The right-most point on the Line object, if one exists. Otherwise, it's
 * * the second Point object given to Line(Point start, Point end).
 * 
 * Methods:
 * Line()
 * * Creates a Line object with both Point objects at (0,0).
 * Line(Point start, Point end)
 * * Creates a Line object with the supplied Point objects.
 * Point GetPointFromX(double x)
 * * Returns a Point object on the Line object at the given x value, or a Point
 * * object with the values x=INFINITY, y=INFINITY if no such Point exists.
 * Point GetPointFromY(double y)
 * * Returns a Point object on the Line object at the given y value, or a Point
 * * object with the values x=INFINITY, y=INFINITY if no such Point exists.
 * bool Collides(Collider &collider)
 * * Redefined from the virtual class Collider. Tests for a collision between
 * * the Line object and the Collider object.
 * void Move(double x, double y)
 * * Redefined from the virtual class Mover. Moves the Line object the
 * * specified distance.
 * void SetPosition(double x, double y)
 * * Redefined from the virtual class Mover. Sets the position of the Line
 * * object to the specified position, relative to the left-most point on the
 * * Line object or the first Point object specified at it's constructor.
 * Double2 GetPosition()
 * * Redefined from the virtual class Mover. Returns a Double2 representing the
 * * position of the Point object, relative to the left-most point on the Line
 * * object or the first Point object specified at it's constructor.
 * Double2 DistanceToTangentPoint(Point &point, int side)
 * * Redefined from the virtual class Mover. If Up or Down is specified, this
 * * method will attempt to find a tangent point at the same x position as the
 * * specified Point object. If Left or Right is specified, this method will
 * * attempt to find a tangent point at the same y position as the specified
 * * Point object.
 */
class Line: public Mover, public Collider {
	friend class Point;
	friend class Bounding;
	friend class Polygon;
	bool Collides(Point &point);
	bool Collides(Bounding &bounding);
	bool Collides(Line &line);
	bool Collides(Polygon &polygon);
public:
	Point start;
	Point end;
	Bounding bounds;
	double slope;
	double yint;

	Line();
	Line(Point start, Point end);

	Point GetPointFromX(double x);
	Point GetPointFromY(double y);

	bool Collides(Collider &collider);

	void Move(double x, double y);
	void SetPosition(double x, double y);
	Double2 GetPosition();
	Double2 DistanceToTangentPoint(Point &point, int side);
};

/* class Polygon
 * Polygon is a collection of Line objects put together into a closed shape.
 *
 * Variables:
 * std::vector<Line> lines
 * * A vector containing the Line objects that make up the Polygon object. The
 * * Line objects are in connecting order.
 * Methods:
 * Polygon()
 * * Creates a Polygon object with no sides.
 * Polygon(std::vector<Point> points)
 * * Creates a Polygon object out of the given Point objects.
 * bool Collides(Collider &collider)
 * * Redefined from the virtual class Collider. Tests for a collision between
 * * the Polygon object and the Collider object.
 * void Move(double x, double y)
 * * Redefined from the virtual class Mover. Moves the Polygon object the
 * * specified distance.
 * void SetPosition(double x, double y)
 * * Redefined from the virtual class Mover. Sets the position of the Polygon
 * * object to the specified position, relative to the first Point object
 * * supplied to it's constructor.
 * Double2 GetPosition()
 * * Redefined from the virtual class Mover. Returns a Double2 representing the
 * * position of the Polygon object, relative to the first Point object given
 * * to it's constructor.
 * Double2 DistanceToTangentPoint(Point &point, int side)
 * * Redefined from the virtual class Mover. If Up or Down is specified, this
 * * method will attempt to find a tangent point at the same x position as the
 * * specified Point object, then tries to find the highest or lowest Point
 * * object with that x position. If Left or Right is specified, this method will
 * * attempt to find a tangent point at the same y position as the specified
 * * Point object, then tries to find the left-most or right-most Point object
 * * with that y position.
 */
class Polygon: public Mover, public Collider {
	friend class Point;
	friend class Bounding;
	friend class Line;
	bool Collides(Point &point);
	bool Collides(Bounding &bounding);
	bool Collides(Line &line);
	bool Collides(Polygon &polygon);
public:
	std::vector<Line> lines;
	Bounding bounds;

	Polygon();
	Polygon(std::vector<Point> points);

	bool Collides(Collider &collider);

	void Move(double x, double y);
	void SetPosition(double x, double y);
	Double2 GetPosition();
	Double2 DistanceToTangentPoint(Point &point, int side);
};

/* class Actor
 * Actor is a virtual class that represents an object that can react to input
 * from an ActorManager object. The Actor class is designed to have
 * user-defined gameplay objects inherit it. User-defined objects only have to
 * override the methods that object will end up using.
 *
 * Methods:
 * std::vector<Collider*> GetColliders()
 * * Called during an ActorManager's collision detection event to retrieve the
 * * Collider objects that represent an Actor for collision tests with other
 * * Collider objects from other Actor objects.
 * void OnCollision(Collider *c1, Collider *c2, Actor *culprit)
 * * Called during an ActorManager's collision detection event when the
 * * Colliders supplied by an Actor's GetColliders method is found to collide
 * * with Colliders from another Actor. Variable c1 is a pointer to the
 * * Collider object retrieved from the Actor. Variable c2 is a pointer to the
 * * foreign Collider object. culprit is a pointer to the Actor that owns c2.
 * void OnKeyboard(int key, int action)
 * * Called on a keyboard key action. Variable key may be any Paunch
 * * constant with the Key prefix. Variable action may be the constants
 * * Press, Release, or Hold.
 * void OnMouseButton(int button, int action, double x, double y)
 * * Called on a mouse button action. Variable button may be any
 * * constant with the MouseButton prefix. Variable action may be Press,
 * * Release, or Hold. Variables x and y are the last reported mouse positions
 * * at the time of the button press.
 * void OnMousePosition(double x, double y)
 * * Called when the cursor is moved. Variables x and y are the new coordinates
 * * of the cursor.
 * void OnWindowResize(int width, int height)
 * * Called when the size of the window has changed. Variables width and height
 * * are the new width and height variables of the window.
 * void OnMouseEnterWindow(double x, double y, bool entered)
 * * Called when the mouse enters or leaves the window. Variables x and y are
 * * the last recorded cursor position. Variable entered is true when the
 * * cursor has entered the window, and false if it has left.
 * void OnWindowFocus(bool focused)
 * * Called when the window has gained or lost focus. Variable focused is true
 * * when the window has focus, and false otherwise.
 * void OnJoystickButton(int button, int action)
 * * Called on a joystick button action. Variable button is an integer
 * * representing the button on the joystick. Variable action can be either
 * * Press, Release, or Hold.
 * void OnJoystickAxis(int device, double value)
 * * Called when the position of a joystick analog component changes. Variable 
 * * device is an integer representing which analog component the event
 * * happened on. Variable value is the axis value of the analog component.
 * void OnJoystickDevice(bool connected)
 * * Called when a joystick is removed or connected. Variable connected is true
 * * if the device was connected, and false otherwise.
 * void OnDraw()
 * * Called during an ActorManager's draw event. Supposed to be used for
 * * rendering.
 * void OnTick()
 * * Called during an ActorManager's tick event. Supposed to be used for
 * * physics and other operations.
 */
class Actor {
public:
	virtual std::vector<Collider*> GetColliders() { return std::vector<Collider*> {}; }
	virtual void OnCollision(Collider *c1, Collider *c2, Actor *culprit) {};
	virtual void OnKeyboard(int key, int action) {};
	virtual void OnMouseButton(int button, int action, double x, double y) {};
	virtual void OnMousePosition(double x, double y) {};
	virtual void OnWindowResize(int width, int height) {};
	virtual void OnMouseEnterWindow(double x, double y, bool entered) {};
	virtual void OnWindowFocus(bool focused) {};
	virtual void OnJoystickButton(int button, int action) {};
	virtual void OnJoystickAxis(int device, double value) {};
	virtual void OnJoystickDevice(bool connected) {};
	virtual void OnDraw() {};
	virtual void OnTick() {};
};

/* class ActorManager
 * ActorManager is a class that's meant to simplify the management of multiple
 * gameplay objects by automating the process of collision detection, drawing,
 * and input management.
 *
 * Methods:
 * ActorManager()
 * * Creates a new ActorManager.
 * void SetActors(std::vector<Actor*> *actors)
 * * Sets the Actor list to the provided vector pointer.
 * std::vector<Actor*> *GetActors()
 * * Returns a pointer to the Actor list vector.
 * void RunKeyboardEvent(int key, int action)
 * * Simulates a keyboard event and notifies Actors in order.
 * void RunMouseButtonEvent(int button, int action, double x, double y)
 * * Simulates a mouse button event and notifies Actors in order.
 * void RunMousePositionEvent(double x, double y)
 * * Simulates a mouse position event and notifies Actors in order.
 * void RunWindowResizeEvent(int width, int height)
 * * Simulates a window resize event and notifies Actors in order.
 * void RunMouseEnterWindowEvent(double x, double y, bool entered)
 * * Simulates a mouse enter window event and notifies Actors in order.
 * void RunWindowFocusEvent(bool focused)
 * * Simulates a window focus event and notifies Actors in order.
 * void RunJoystickButtonEvent(int button, int action)
 * * Simulates a joystick button event and notifies Actors in order.
 * void RunJoystickAxisEvent(int device, double value)
 * * Simulates a joystick axis event and notifies Actors in order.
 * void RunJoystickDeviceEvent(bool connected)
 * * Simulates a joystick device event and notifies Actors in order.
 * void RunCollisionEvent()
 * * Runs a collision check event.
 * void RunDrawEvent()
 * * Runs a drawing event.
 */
class ActorManager {
	std::vector<Actor*> *actors;
public:
	ActorManager();
	void SetActors(std::vector<Actor*> *actors);
	std::vector<Actor*> *GetActors();

	void RunKeyboardEvent(int key, int action);
	void RunMouseButtonEvent(int button, int action, double x, double y);
	void RunMousePositionEvent(double x, double y);
	void RunWindowResizeEvent(int width, int height);
	void RunMouseEnterWindowEvent(double x, double y, bool entered);
	void RunWindowFocusEvent(bool focused);
	void RunJoystickButtonEvent(int button, int action);
	void RunJoystickAxisEvent(int device, double value);
	void RunJoystickDeviceEvent(bool connected);
	void RunCollisionEvent();
	void RunTickEvent();
	void RunDrawEvent();
};

class force {
public:
	Double2 magnitude;
	bool active;
};

/* class Physics
 * Physics is a class that is designed to simplify the complex movement of
 * multiple objects at once. It provides methods to aid in realistic movement
 * by automating object acceleration. The user may be create a constant source
 * of acceleration by creating an enabling a force.
 *
 * Methods:
 * Physics()
 * * Creates a new Physics object.
 * void SetMovers(std::vector<Mover*> *movers)
 * * Sets the list of Mover objects to the given vector pointer.
 * std::vector<Mover*> *GetMovers()
 * * Returns a pointer to the list of Mover objects.
 * void AddForce(std::string name, double forceX, double forceY)
 * * Creates a new force or edits an existing force using the given values. New
 * * forces are disabled by default.
 * void EnableForce(std::string name)
 * * Enables the force associated with the given name. The method does nothing
 * * if no such force exists or if the force is already enabled.
 * void DisableForce(std::string name)
 * * Disables the force associated with the given name. The method does nothing
 * * if no such force exists or if the force is already disabled.
 * void DeleteForce(std::string name)
 * * Deletes a force associated with the given name. The method does nothing if
 * * the force does not exist.
 * void Accelerate(double forceX, double forceY)
 * * Accelerates the Mover objects the specified magnitude.
 * void SetAcceleration(double force, int axis)
 * * Sets the acceleration of the Mover objects to the specified magnitude on
 * * the specified axis. Variable axis may be either constants X or Y.
 * void SetAcceleration(double forceX, double forceY)
 * * Sets the acceleration of the Mover objects to the specified magnitudes.
 * Double2 GetAcceleration()
 * * Returns a Double2 representing the acceleration of the Physics object in
 * * the X and Y directions.
 * double GetAcceleration(int axis)
 * * Returns the acceleration of the Physics object in the specified direction.
 * * Variable axis may be either constants X or Y.
 * void SetMaxAcceleration(double force, int axis)
 * * Sets the maximum allowed acceleration of the Physics object to the
 * * specified magnitude on the specified axis. Variable axis may be either
 * * constants X or Y.
 * void SetMaxAcceleration(double forceX, double forceY)
 * * Sets the maximum allowed acceleration of the Physics object to the
 * * specified magnitude.
 * void SetMinAcceleration(double force, int axis);
 * * Sets the minimum allowed acceleration of the Physics object to the
 * * specified magnitude on the specified axis. Variable axis may be either
 * * constants X or Y.
 * void SetMinAcceleration(double forceX, double forceY)
 * * Sets the minimum allowed acceleration of the Physics object to the
 * * specified magnitude.
 * void SetFriction(double force, int axis)
 * * Sets the friction, or the force that encourages acceleration to approach
 * * zero, in the specified direction. Variable axis may be either constants X
 * * or Y.
 * void SetFriction(double forceX, double forceY)
 * * Sets the friction, or the force that encourages acceleration to approacch
 * * zero.
 * void Calculate()
 * * Applies all enabled forces and the acceleration to the Physics object's
 * * Movers.
 * void Move(double x, double y)
 * * Redefined from the virtual class Mover. Moves the Physics object's Movers
 * * the specified distance.
 * void SetPosition(double x, double y)
 * * Redefined from the virtual class Mover. Sets the position of the first
 * * Physics object's Mover to the specified position, and moves all other
 * * Movers the distance the first Mover object ended up traveling.
 * Double2 GetPosition()
 * * Redefined from the virtual class Mover. Returns a Double2 representing the
 * * position of the Physics object's first Mover.
 */
class Physics: public Mover {
	std::vector<Mover*> *movers;
	Double2 accel;
	Double2 maxAccel;
	Double2 minAccel;
	Double2 friction;
	std::map<int, bool> usingMaxAccel;
	std::map<int, bool> usingMinAccel;
	std::map<std::string, force> forces;
public:
	Physics();
	void SetMovers(std::vector<Mover*> *movers);
	std::vector<Mover*> *GetMovers();
	void AddForce(std::string name, double forceX, double forceY);
	void EnableForce(std::string name);
	void DisableForce(std::string name);
	void DeleteForce(std::string name);
	void Accelerate(double forceX, double forceY);
	void SetAcceleration(double force, int axis);
	void SetAcceleration(double forceX, double forceY);
	Double2 GetAcceleration();
	double GetAcceleration(int axis);
	void SetMaxAcceleration(double force, int axis);
	void SetMaxAcceleration(double forceX, double forceY);
	void SetMinAcceleration(double force, int axis);
	void SetMinAcceleration(double forceX, double forceY);
	void SetFriction(double force, int axis);
	void SetFriction(double forceX, double forceY);
	void Calculate();

	void Move(double x, double y);
	void SetPosition(double x, double y);
	Double2 GetPosition();
};

/* void InitDraw()
 * Sets up the drawing session for use.
 */
void InitDraw();

/* void Clear()
 * Clears the screen.
 */
void Clear();

/* class Effect
 * Effect is a class that manages GLSL shaders.
 *
 * Methods:
 * Effect()
 * * Creates a new empty Effect object.
 * Effect(std::vector<std::string> filenames)
 * * Creates a new Effect object based on the GLSL shader files given.
 * Effect(std::vector<std::string> scripts, std::vector<int> types)
 * * Creates a new Effect object based on the GLSL shader strings given. The
 * * vector "types" should be either Vertex or Fragment.
 * SetVariable[2/3/4][i/ui/f](std::string variable, ...)
 * * Sets a uniform variable to the given values.
 */
class Effect {
	std::map<std::string, GLint> uniforms;
	GLuint program;

	void checkUniformVariable(std::string variable);
public:
	Effect();
	Effect(std::vector<std::string> filenames);
	Effect(std::vector<std::string> scripts, std::vector<int> types);

	void SetVariablei(std::string variable, int val);
	void SetVariable2i(std::string variable, int val1, int val2);
	void SetVariable3i(std::string variable, int val1, int val2, int val3);
	void SetVariable4i(std::string variable, int val1, int val2, int val3, int val4);
	void SetVariableui(std::string variable, unsigned int val);
	void SetVariable2ui(std::string variable, unsigned int val1, unsigned int val2);
	void SetVariable3ui(std::string variable, unsigned int val1, unsigned int val2, unsigned int val3);
	void SetVariable4ui(std::string variable, unsigned int val1, unsigned int val2, unsigned int val3, unsigned int val4);
	void SetVariablef(std::string variable, float val);
	void SetVariable2f(std::string variable, float val1, float val2);
	void SetVariable3f(std::string variable, float val1, float val2, float val3);
	void SetVariable4f(std::string variable, float val1, float val2, float val3, float val4);

	GLuint getProgramID();
};

/* void UseEffect(Effect *effect)
 * Sets the given Effect object to be the active effect for future drawing
 * commands.
 */
void UseEffect(Effect *effect);

/* void DisableEffects()
 * Disables effects.
 */
void DisableEffects();

/* class Renderable
 * Renderable is a class that represents a drawable object.
 *
 * Methods:
 * Renderable()
 * * Creates a new empty Renderable object.
 * Renderable(int mode, std::vector<double> verticies)
 * * Creates a new Renderable object using the supplied vector of verticies.
 * * Variable mode could be either Points, LineStrip, LineLoop, Lines,
 * * TriangleStrip, TriangleFan, or Triangles.
 * Renderable(double x, double y, double width, double height, std::string filename, int clip)
 * * Creates a rectangular, textured Renderable object. Variables width and
 * * height of each individual clip. Variable clip is how many sections the
 * * image should be vertically clipped to.
 * void Texture(std::vector<double> coords, std::string filename, int clip)
 * * Textures the Renderable object using the given texture coordinates.
 * * Variable clip is how many sections the image should be vertically clipped
 * * to.
 * void Draw(int frame)
 * * Draws the Renderable object on screen. Variable frame represents which
 * * clip the Renderable object should be drawn with.
 * void Move(double x, double y)
 * * Redefined from the virtual class Mover. Moves the Renderable object the
 * * specified distance relative to the first vertex supplied or the bottom
 * * left corner if the auto-texture constructor was used.
 * void SetPosition(double x, double y)
 * * Redefined from the virtual class Mover. Sets the position of the
 * * Renderable object relative to the first vertex supplied or the bottom
 * * left corner if the auto-texture constructor was used.
 * Double2 GetPosition()
 * * Redefined from the virtual class Mover. Returns the position of the
 * * Renderable object relative to the first vertex supplied or the bottom
 * * left corner if the auto-texture constructor was used.
 */
class Renderable: public Mover {
	int mode;
	GLuint vertexBuffer;
	GLuint texcoordBuffer;
	std::vector<GLuint> textures;
	std::vector<float> verticies;

public:
	Renderable();
	Renderable(int mode, std::vector<double> verticies);
	Renderable(double x, double y, double width, double height, std::string filename, int clip);

	void Texture(std::vector<double> coords, std::string filename, int clip);
	void Draw(int frame);

	void Move(double x, double y);
	void SetPosition(double x, double y);
	Double2 GetPosition();
};

/* void InitWindows()
 * Initializes the window system for use.
 */
void InitWindows();

/* class Window
 * Window is a class that manages window creation and user input.
 *
 * Methods:
 * Window()
 * * Creates a new Window object.
 * Window(int width, int height, int nativeWidth, int nativeHeight, bool fullscreen, std::string title)
 * * Creates a new Window object. The width and height will be the size of the
 * * window in pixels. The nativeWidth and nativeHeight represent the actual
 * * width and height of the drawing space if it were not stretched to
 * * accomidate the window size. This is only important when SetNativeMousePos
 * * is enabled.
 * void Open()
 * * Opens the window.
 * void Close()
 * * Closes the window.
 * void UpdateDisplay()
 * * Updates the display in the window.
 * void UpdateEvents()
 * * Reads new input events.
 * bool ShouldClose()
 * * Returns true if the user has attempted to close the window.
 * void SetFullscreen(bool fullscreen)
 * * Sets whether or not the window is fullscreen.
 * bool GetFullscreen()
 * * Returns true if the window is fullscreen.
 * Int2 GetSize()
 * * Returns an Int2 representing the size of the window.
 * void SetSize(int width, int height)
 * * Sets the width and height of the window.
 * Int2 GetNativeSize()
 * * Returns an Int2 representing the native size of the window.
 * void SetNativeSize(int nativeWidth, int nativeHeight)
 * * Sets the native size of the window.
 * void SetNativeMouseCorrection(bool shouldBeNative)
 * * Changes the behavior of the reported mouse position. If enabled, supplied
 * * mouse positions are made relative to the native width and native height of
 * * the Window object. This is useful for applications that stretch to larger
 * * window sizes, so that mouse position behavior remains the same regardless
 * * of window size.
 * bool GetNativeMouseCorrection()
 * * Returns true if native mouse correction is enabled.
 * bool GetKeyState(int key)
 * * Returns true if the specified key is pressed.
 * bool GetMouseButtonState(int button)
 * * Returns true if the specified mouse button is pressed.
 * void SetActorManagers(std::vector<ActorManager*> *actorManagers)
 * * Sets which ActorManager objects will be notified on a user input event.
 * std::vector<ActorManager*> *GetActorManagers()
 * * Returns a pointer to the ActorManager list being used.
 * Double2 GetCursorPosition()
 * * Returns a Double2 representing the last reported mouse position in the
 * * window.
 * bool CheckForJoystick()
 * * Returns true if a joystick is connected.
 */
class Window {
	Int2 size, nativeSize;
	std::string title;
	bool nativeMousePos;
	GLFWwindow *glfw;
	std::vector<ActorManager*> *actorManagers;

	std::map<int, bool> keyStates;
	std::map<int, bool> mouseButtonStates;
	Double2 mousePos;
	std::map<int, bool> joyBtnStates;
	std::map<int, float> joyAxisStates;
	bool isJoystick;
	bool fullscreen;

public:
	Window();
	Window(int width, int height, int nativeWidth, int nativeHeight, bool fullscreen, std::string title);
	~Window();

	void Open();
	void Close();
	void UpdateDisplay();
	void UpdateEvents();
	bool ShouldClose();
	void SetFullscreen(bool fullscreen);
	bool GetFullscreen();
	Int2 GetSize();
	void SetSize(int width, int height);
	Int2 GetNativeSize();
	void SetNativeSize(int nativeWidth, int nativeHeight);
	void SetNativeMouseCorrection(bool shouldBeNative);
	bool GetNativeMouseCorrection();
	bool GetKeyState(int key);
	void _setKeyState(int key, bool state);
	bool GetMouseButtonState(int button);
	void _setMouseButtonState(int button, bool state);
	void SetActorManagers(std::vector<ActorManager*> *actorManagers);
	std::vector<ActorManager*> *GetActorManagers();
	Double2 GetCursorPosition();
	bool CheckForJoystick();
};

/* class Audio
 * Audio is a class that manages the Paunch sound system.
 *
 * Audio()
 * * Creates a new Audio object. This must be called before any other audio-
 * * based events happen.
 */
class Audio {
	ALCcontext *context;
	ALCdevice *device;
public:
	Audio();
	~Audio();
};

/* class Sound
 * Sound is a class that represents a playable sound.
 *
 * Sound()
 * * Creates an empty Sound object.
 * Sound(std::string filename)
 * * Creates a new Sound object based on the sound file given. Only OGG Vorbis
 * * files are supported.
 * void Play()
 * * Plays the sound.
 * void Pause()
 * * Pauses the sound.
 * void Stop()
 * * Stops the sound and resets the playhead to the beginning.
 * void SetLoop(bool loop)
 * * Sets whether or not the sound will loop when played.
 * int GetState()
 * * Returns the play state of the Sound object.
 * float GetGain()
 * * Returns the gain of the Sound object.
 * void SetGain(float gain)
 * * Sets the gain of the Sound object.
 */
class Sound {
	ALuint source;
	ALuint buffer;
	int sampleRate;
	int numChannels;
public:
	Sound();
	Sound(std::string filename);
	~Sound();
	void Play();
	void Pause();
	void Stop();
	void SetLoop(bool loop);
	int GetState();
	float GetGain();
	void SetGain(float gain);
};

}


#endif // PAUNCH_H_

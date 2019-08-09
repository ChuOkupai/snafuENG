#include <errno.h>
#include <snafuENG.h>

const char*	snf_ktoa(int c)
{
	if (c == SNFKEY_ARROW_UP)		return ("up");
	if (c == SNFKEY_ARROW_DOWN)		return ("down");
	if (c == SNFKEY_ARROW_RIGHT)	return ("right");
	if (c == SNFKEY_ARROW_LEFT)		return ("left");
	if (c == SNFKEY_HOME)			return ("home");
	if (c == SNFKEY_INS)			return ("insert");
	if (c == SNFKEY_DEL)			return ("delete");
	if (c == SNFKEY_END)			return ("end");
	if (c == SNFKEY_PAGE_UP)		return ("page up");
	if (c == SNFKEY_PAGE_DOWN)		return ("page down");
	errno = EINVAL; 
	snf_error(__func__, false);
	return ("");
}

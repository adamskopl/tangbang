/* 
 This file is part of Tangbang.

 Tangbang is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Tangbang is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Tangbang.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "node.h"

bool node::hasParent() {
	if (parent)
		return true;
	else
		return false;
}

bool node::hasChild() {
	if (child)
		return true;
	else
		return false;
}

bool node::isFirst() {
	if (parent)
		return (parent->child == this);
	else
		return false;
}

bool node::isLast() {
	if (parent)
		return (parent->child->prev == this);
	else
		return false;
}

void node::connectTo(node* newParent) {
	if (parent)
		disconnect();

	parent = newParent;

	if (parent->child) {
		prev = parent->child->prev;
		next = parent->child;
		parent->child->prev->next = this;
		parent->child->prev = this;
	} else {
		parent->child = this;
	}
}

void node::connect(node* newChild) {
	if (newChild->hasParent())
		newChild->disconnect();

	newChild->parent = this;

	if (child) {
		newChild->prev = child->prev;
		newChild->next = child;
		child->prev->next = newChild;
		child->prev = newChild;
	} else
		child = newChild;
}

void node::disconnect() {
	if (parent && parent->child == this) {
		if (next != this)
			parent->child = next;
		else
			parent->child = NULL;
	}

	prev->next = next;
	next->prev = prev;

	prev = this;
	next = this;
}

node::node() {
	parent = NULL;
	child = NULL;
	prev = this;
	next = this;
}

node::node(node* node) {

	parent = NULL;
	child = NULL;
	prev = this;
	next = this;
	connectTo(node);
}

//existence of parent should be checked first
node* node::giveFirst() {
	if (parent->child == this)
		return this;

	return prev->giveFirst();
}

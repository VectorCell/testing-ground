#!/usr/bin/env python3

class MyClass:

	def __init__(self):
		self.x = 'x'
		self._y = 'y'
		self.__z = 'z'

	def  __repr__(self):
		return 'This is a representation of a MyClass object'


def main ():
	mc = MyClass()
	attributes = dir(mc)
	attributes.append('hello')
	for attr in (a for a in dir(mc) if a not in dir(MyClass)):
		print(attr, '::', type(getattr(mc, attr)), '::', getattr(mc, attr))


if __name__ == '__main__':
	main()

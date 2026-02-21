Typelists are used to manage a collection of types a replacement for variadics.

Why do you need typelists -> want to prevent repetition.

Want to generalize the base code:
`class WidgetFactory {`
`public:`
	`virtual Window* CreateWindow() = 0;`
	`virtual Button* CreateButton() = 0;`
`}`

Before c++ 11 you cannot have variable number of parameters.

`template <typename T>`
`T* MakeWidget(WidgetFactory& factory)`
`{`
`T* widget = factory.Create<T>();`
`return widget;`
`}`


You cannot templatize virtual functions so this will not work.



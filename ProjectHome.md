# FROST #

software for a dance performance
_recoil performance group, fall 2009_

an interactive video scenography for a recoil performance group dance performance/installation. developed with choreographer tina tarpgaard and programmers ole kristensen and jonas jongejan.

http://olekristensen.files.wordpress.com/2009/10/mg_0068a.jpg?h=250
http://olekristensen.files.wordpress.com/2009/10/360.jpg?h=250

### Description ###

working with the talented dancers of danish dance theatre, we created a universe of frozen bodies, melting ice and dripping waters. the scenography is primarily consisting of video projections in concert with andreas buhl’s lighting design, primarily using led based light sources to accomodate the intricacies of infrared tracking.

frost was from the outset designed to be tour-friendly and as such our software has to be flexible and easily adjustable for different stage dimensions.

### Technology ###

the software is open source and we are very grateful to the openframeworks community, whose efforts form the basis of our programming work. the software for frost intergrates openframeworks into a cocoa-based mac os x snow leopard application running on a mac pro seeing the dancers through three point grey flea 2 ieee 1394b cameras, showing the opengl graphics using a single video projector with a 0.7 wide angle optics and qued from qlab using apple’s midi networking capabilities.

### Code Disclaimer ###

it’s messy, it’s the first time we did something in cocoa and objective c, but it’s there. run at your own risk.
the apps compile on a mac using xcode. you also need open frameworks. while the code is full of all kinds of nice trickeries, the application itself is not of much use outside the scope of our performance. apart from a quite big space and a professional dance company, it works tightly together with custom hardware and third party apps such as qlab – not even mentioning the lib dependencies…

... so read if you please, compile if you can - but don't expect it to compute for you
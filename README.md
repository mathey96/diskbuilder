## about

Had an idea about this project when my friends
had a rough time coming up with counting the disks up to a certain sum.  


Hopefully this will help out your local small and dedicated
community of warhammer diskwars to grow even larger, with less bore-you-to-death game setups.  


Anyway, this is pretty much a classic dynamic programming
coin change problem, - i.e count ways to make a sum:  
(https://en.wikipedia.org/wiki/Change-making_problem)  
but with a few twists and limitations
(eg. number of disks available to player and other - and all other details you can research on snipertroll's webpage:  
(https://snipertroll.wordpress.com/2014/05/20/army-building/)  


While app is written in C++, it can be deployed to web using emscripten's WASM magic, ready to be used by your local gang of four.  


## demo
![](https://github.com/mathey96/diskbuilder/blob/master/demo.gif)

https://github.com/user-attachments/assets/2219709b-8b1c-444d-9b92-7827554799c4

## hosting
get your local python server serving a html page like this:  

~~~ console
python -m http.server  
~~~
then get your ngrok or similar opensource service to run this on the web to be readily available to your local lads and lasses.  

### ngrok
host locally to your friends like this:  
~~~ console
ngrok http 8080
~~~

Happy disk flippin'  

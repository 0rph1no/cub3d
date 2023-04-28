#Specifically to note things for the project

pick each cube(object in the map) with 60px width height

fov means the field of vue that the player see, its like the cam range from the player perspective.

the hall purpose of the drawing is just calculating the distance between the player position and the first hitted wall or obstacle becz that will indicates how long the wall will be
the lower the distance the bigger the wall and vice versa

i need to know the fov width aka the projection plane then indicate the angle degree from the player to that fov for ex if the angle is 60deggrees.
and the fov width is 320px that means the slice between one ray and the second will be 60rad/320...


dimensions={
	"fov": "60",
	"wall high" : "60px",
	"assumed player height" : "32px,
	""

}

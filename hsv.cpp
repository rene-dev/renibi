#include "alles.h"

 float Ppm::maxrgb(float r,float g,float b)
 {
   float max;

   if( r > g)
     max = r;
   else
     max = g;
   if( b > max )
     max = b;
   return( max );
 }


 float Ppm::minrgb(float r,float g,float b)
 {
   float min;

   if( r < g)
     min = r;
   else
     min = g;
   if( b < min )
     min = b;
   return( min );
 }


var_color Ppm::hsv2rgb(var_color in)
 {
	float hin, s, v;
   float h;
   float r=0,g=0,b=0;
   float f,p,q,t;
   int i;
	var_color out;

	hin = (float)in.r / 255 * 360;
	s = (float)in.g / 255;
	v = (float)in.b / 255;

// cout << hin << " " << s << " " << v << endl << flush;

   h = hin;
   if( s == 0 ) {
     r = v;
     g = v;
     b = v;
   }
   else {
     if(h == 360.)
       h = 0.0;
     h /= 60.;
     i = (int) h;
     f = h - i;
     p = v*(1-s);
     q = v*(1-(s*f));
     t = v*(1-s*(1-f));
     switch(i) {
     case 0:
       r = v;
       g = t;
       b = p;
       break;
     case 1:
       r = q;
       g = v;
       b = p;
       break;
     case 2:
       r = p;
       g = v;
       b = t;
       break;
     case 3:
       r = p;
       g = q;
       b = v;
       break;
     case 4:
       r = t;
       g = p;
       b = v;
       break;
     case 5:
       r = v;
       g = p;
       b = q;
       break;
     default:
       r = 1.0;
       g = 1.0;
       b = 1.0;
       printf("hsv2rgb::How did I get here?\n");
       printf("h: %f, s: %f, v: %f; i:  %d\n",hin,s,v,i);
       break;
     }
   }
   out.r = static_cast <unsigned char> (r * 255);
   out.g = static_cast <unsigned char> (g * 255);
   out.b = static_cast <unsigned char> (b * 255);
	return(out);
 }

bool Ppm::hsv2rgbpix(void){
	var_pos pos;
	pos = filter.p1;
 	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
		setpix(pos,hsv2rgb(getpix(pos)));
		pos.x++;
		}
	pos.y++;
	}
	return (true);
}

bool Ppm::rgb2hsvpix(void){
	var_pos pos;
	pos = filter.p1;
 	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
		setpix(pos,rgb2hsv(getpix(pos)));
		pos.x++;
		}
	pos.y++;
	}
	return (true);
}


 var_color Ppm::rgb2hsv(var_color in)
 {
	float r, g, b;
	var_color out;

	r = (float)in.r / 255;
	g = (float)in.g / 255;
	b = (float)in.b / 255;

   float h=0,s=1.0,v=1.0;
   float max_v,min_v,diff,r_dist,g_dist,b_dist;
   float undefined = 0.0;

   max_v = maxrgb(r,g,b);
   min_v = minrgb(r,g,b);
   diff = max_v - min_v;
   v = max_v;

   if( max_v != 0 )
     s = diff/max_v;
   else
     s = 0.0;
   if( s == 0 )
     h = undefined;
   else {
     r_dist = (max_v - r)/diff;
     g_dist = (max_v - g)/diff;
     b_dist = (max_v - b)/diff;
     if( r == max_v )
       h = b_dist - g_dist;
     else
       if( g == max_v )
         h = 2 + r_dist - b_dist;
       else
         if( b == max_v )
           h = 4 + g_dist - r_dist;
         else
           printf("rgb2hsv::How did I get here?\n");
     h *= 60;
     if( h < 0)
       h += 360.0;
   }
   out.r = (unsigned char) (h / 360 * 254) + 1;
   out.g = (unsigned char) (s * 255);
   out.b = (unsigned char) (v * 255);
	if(out.g < 90 || out.b < 50){
	out.r = 0;
	}
	return(out);
 }




#version 330
#define N 4
//Zmienne interpolowane
in vec2 iTexCoord;
in vec4 l[N];
in vec4 n;
in vec4 v;

uniform sampler2D textureMap; //Jednostka teksturująca 0

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

void main(void) {
    vec4 kd=texture(textureMap, iTexCoord); //Kolor materia³u dla œwiat³a rozpraszanego
    vec4 ld=vec4(0.5,0.5,0.5,0.5); //Kolor œwiat³a rozpraszanwego
    vec4 ks=vec4(1,1,1,1); //Kolor odbiæ materia³u
    vec4 ls=vec4(0.8,0.8,0.8,0.8); //Kolor œwiat³a odbijanego


    vec4 mn=normalize(n);
    vec4 mv=normalize(v);
    vec4 mr[N];
    vec4 ml[N];
    float rv[N];
    vec3 sum;
    float nl[N];
    for(int i = 0; i < N; i++)
    {
        ml[i] = normalize(l[i]);
        mr[i] = reflect(-ml[i], mn);
        rv[i] = pow(clamp(dot(mr[i],mv),0,1),25);
        nl[i]=clamp(dot(mn,ml[i]),0,1); //cos k¹ta pomiêdzy wektorami n i l
       if(i==0)
       {
           sum=kd.rgb*ld.rgb*nl[i]+ks.rgb*ls.rgb*rv[i];
       }
       else
        {
        sum= sum + kd.rgb*ld.rgb*nl[i]+ks.rgb*ls.rgb*rv[i];
       }
    }

    pixelColor=vec4(sum,kd.a);
}

#version 450

layout (location = 0) in vec2 fragOffset;
layout (location = 0) out vec4 outColour;

struct PointLight 
{
  vec4 position; // ignore w
  vec4 Colour; // w is intensity
};

layout(set = 0, binding = 0) uniform GlobalUbo 
{
  mat4 projection;
  mat4 view;
  mat4 inverseView;
  vec4 ambientLightColour; // w is intensity
  PointLight pointLights[10];
  int numLights;
} ubo;

layout(push_constant) uniform Push 
{
  vec4 position;
  vec4 Colour;
  float radius;
} push;

const float M_PI = 3.1415926538;

void main() 
{
  float dis = sqrt(dot(fragOffset, fragOffset));
  if (dis >= 1.0) 
  {
    discard;
  }
  float cosDis = 0.5 * (cos(dis * M_PI) + 1.0);
  outColour = vec4(push.Colour.xyz * 0.5 * cosDis, cosDis);
}
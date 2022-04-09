# CPU_RayTracing
This is my repository for Advance Tech CPU RayTracing

![Image](https://github.com/kieranbow/CPU_RayTracing/blob/main/Images/Image.png)

## Introduction
The task was to create a cpu raytracer in C++ that could render images and include features like Bounding Volume Hierarchy, Multi-threading, different materials etc.

## Project Features
The features that were developed for this project are:
- Multi-Threading
- Bounding Volume Hierarchy
- Reflective and refractive materials
- Diffuse materials using Cook-Torrance BRDF
- Mesh loading using Assimp https://github.com/assimp/assimp
- Texture loading using stb https://github.com/nothings/stb/blob/master/stb_image.h
- Tile Based rendering
- Multiple Directional Lights
- Physically Based sky-box

## Instructions
In order to build this project for debug or release, assimp-vc142-mtd.dll from CPU_RayTracing\AT_CPU_RayTracing\dll needs to be place inside CPU_RayTracing\x64\Debug or CPU_RayTracing\x64\Release.

## Screenshots
![Sunset](https://github.com/kieranbow/CPU_RayTracing/blob/main/Images/sunset.png)
> A sunset

![reflect](https://github.com/kieranbow/CPU_RayTracing/blob/main/Images/Reflective%20model.png)
> Two reflective sphere

![Cook](https://github.com/kieranbow/CPU_RayTracing/blob/main/Images/Cook%20Model.png)
> Left: Roughness 0.2, Metallic 0
> Right: Roughness 0.5, Metallic 1.0

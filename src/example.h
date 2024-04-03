#include <iostream>

#include "bvh.h"
#include "camera.h"
#include "color.h"
#include "constant_medium.h"
#include "external/log.h"
#include "external/params.h"
#include "hittable_list.h"
#include "material.h"
#include "quad.h"
#include "rtweekend.h"
#include "sphere.h"
#include "texture.h"

hittable_list get_ligths()
{
    // Light Sources
    hittable_list lights;
    auto m = shared_ptr<material>();

    point3 origin(343, 554, 332);
    vec3 dir1(-130, 0, 0);
    vec3 dir2(0, 0, -105);

    LOG(DEBUG) << "Initialize light source for material " << m << ", with shape 'QUAD':";
    LOG(DEBUG) << " - origin: " << origin;
    LOG(DEBUG) << " - direction 1: " << dir1;
    LOG(DEBUG) << " - direction 2: " << dir2;
    lights.add(make_shared<quad>(origin, dir1, dir2, m));

    point3 origin1(190, 90, 190);
    int rad = 90;
    LOG(DEBUG) << "Initialize light source for material " << m << ", with shape 'SPHERE':";
    LOG(DEBUG) << " - origin: " << origin1;
    LOG(DEBUG) << " - radius: " << rad;
    lights.add(make_shared<sphere>(origin1, rad, m));

    return lights;
}

camera initialize_camera(const point3 &lookfrom, const point3 &lookat, const vec3 &vup, double vfov,
                         double aspect_ratio, int image_width, int samples_per_pixel, int max_depth,
                         double defocus_angle, double focus_dist, color color)
{
    LOG(DEBUG) << "Initializing Camera with Parameters:";
    LOG(DEBUG) << "  - Look From: " << lookfrom;
    LOG(DEBUG) << "  - Look At: " << lookat;
    LOG(DEBUG) << "  - View Up: " << vup;
    LOG(DEBUG) << "  - Vertical FOV: " << vfov;
    LOG(DEBUG) << "  - Aspect Ratio: " << aspect_ratio;
    LOG(DEBUG) << "  - Image Width: " << image_width;
    LOG(DEBUG) << "  - Samples per Pixel: " << samples_per_pixel;
    LOG(DEBUG) << "  - Max Depth: " << max_depth;
    LOG(DEBUG) << "  - Defocus Angle: " << defocus_angle;
    LOG(DEBUG) << "  - Focus Distance: " << focus_dist;
    LOG(DEBUG) << "  - Background Color: " << color;

    camera cam;

    cam.aspect_ratio = aspect_ratio;
    cam.image_width = image_width;
    cam.samples_per_pixel = samples_per_pixel;
    cam.max_depth = max_depth;

    cam.vfov = vfov;
    cam.lookfrom = lookfrom;
    cam.lookat = lookat;
    cam.vup = vup;

    cam.defocus_angle = defocus_angle;
    cam.focus_dist = focus_dist;

    cam.background = color;

    return cam;
}

void random_spheres(RenderParameters params, int start = -11, int end = 11)
{
    // World
    hittable_list world;

    auto checker = make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(checker)));

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    LOG(DEBUG) << "CREATE APPROXIMATELY " << std::fabs(start * end) << " SPHERICAL OBJECTS";
    int m, g = 0;
    for (int a = start; a < end; a++)
    {
        for (int b = start; b < end; b++)
        {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9)
            {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8)
                {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random_double(0, 0.5), 0);
                    world.add(make_shared<sphere>(center, center2, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    m++;
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    g++;
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    LOG(DEBUG) << "CREATED AND DISPLAYED " << m + g << " SPHERES OF MATERIALS:\n\tMETAL: " << m << "\n\tGLASS: " << g;

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    world = hittable_list(make_shared<bvh_node>(world));

    camera cam = initialize_camera(params.lookfrom, params.lookat, params.vup, params.vfov, params.aspect_ratio,
                                   params.image_width, params.samples_per_pixel, params.max_depth, params.defocus_angle,
                                   params.focus_dist, params.c);
    LOG(INFO) << "START RENDERING";
    cam.render(world, get_ligths());
    LOG(INFO) << "END RENDERING\n";
}

void two_spheres(RenderParameters params)
{
    // World
    hittable_list world;

    auto checker = make_shared<checker_texture>(0.8, color(.2, .3, .1), color(.9, .9, .9));
    auto material = make_shared<lambertian>(checker);
    world.add(make_shared<sphere>(point3(0, 10, 0), 10, material));
    world.add(make_shared<sphere>(point3(0, -10, 0), 10, material));

    camera cam = initialize_camera(params.lookfrom, params.lookat, params.vup, params.vfov, params.aspect_ratio,
                                   params.image_width, params.samples_per_pixel, params.max_depth, params.defocus_angle,
                                   params.focus_dist, params.c);
    LOG(INFO) << "START RENDERING";
    cam.render(world, get_ligths());
    LOG(INFO) << "END RENDERING\n";
}

void earth(RenderParameters params)
{

    // World
    hittable_list world;

    auto earth_texture = make_shared<image_texture>(".\\img\\earthmap.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto globe = make_shared<sphere>(point3(0, 0, 0), 2, earth_surface);

    camera cam = initialize_camera(point3(0, 0, 12), params.lookat, params.vup, params.vfov, params.aspect_ratio,
                                   params.image_width, params.samples_per_pixel, params.max_depth, params.defocus_angle,
                                   params.focus_dist, params.c);
    LOG(INFO) << "START RENDERING";
    cam.render(world, get_ligths());
    LOG(INFO) << "END RENDERING\n";
}

void two_perlin_spheres(RenderParameters params)
{
    hittable_list world;

    auto pertext = make_shared<noise_texture>(4);
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    world.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));

    camera cam = initialize_camera(params.lookfrom, params.lookat, params.vup, params.vfov, params.aspect_ratio,
                                   params.image_width, params.samples_per_pixel, params.max_depth, 0, params.focus_dist,
                                   params.c);
    LOG(INFO) << "START RENDERING";
    cam.render(world, get_ligths());
    LOG(INFO) << "END RENDERING\n";
}

void quads(RenderParameters params)
{
    hittable_list world;

    // Materials
    auto left_red = make_shared<lambertian>(color(1.0, 0.2, 0.2));
    auto back_green = make_shared<lambertian>(color(0.2, 1.0, 0.2));
    auto right_blue = make_shared<lambertian>(color(0.2, 0.2, 1.0));
    auto upper_orange = make_shared<lambertian>(color(1.0, 0.5, 0.0));
    auto lower_teal = make_shared<lambertian>(color(0.2, 0.8, 0.8));

    // Quads
    world.add(make_shared<quad>(point3(-3, -2, 5), vec3(0, 0, -4), vec3(0, 4, 0), left_red));
    world.add(make_shared<quad>(point3(-2, -2, 0), vec3(4, 0, 0), vec3(0, 4, 0), back_green));
    world.add(make_shared<quad>(point3(3, -2, 1), vec3(0, 0, 4), vec3(0, 4, 0), right_blue));
    world.add(make_shared<quad>(point3(-2, 3, 1), vec3(4, 0, 0), vec3(0, 0, 4), upper_orange));
    world.add(make_shared<quad>(point3(-2, -3, 5), vec3(4, 0, 0), vec3(0, 0, -4), lower_teal));

    camera cam =
        initialize_camera(point3(0, 0, 9), params.lookat, params.vup, 80, params.aspect_ratio, params.image_width,
                          params.samples_per_pixel, params.max_depth, 0, params.focus_dist, params.c);

    LOG(INFO) << "START RENDERING";
    cam.render(world, get_ligths());
    LOG(INFO) << "END RENDERING\n";
}

void simple_light(RenderParameters params)
{
    hittable_list world;

    auto pertext = make_shared<noise_texture>(4);
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    world.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));

    auto difflight = make_shared<diffuse_light>(color(4, 4, 4));
    world.add(make_shared<sphere>(point3(0, 7, 0), 2, difflight));
    world.add(make_shared<quad>(point3(3, 1, -2), vec3(2, 0, 0), vec3(0, 2, 0), difflight));

    camera cam = initialize_camera(point3(26, 3, 6), point3(0, 2, 0), params.vup, params.vfov, params.aspect_ratio,
                                   params.image_width, params.samples_per_pixel, params.max_depth, 0, params.focus_dist,
                                   params.c);

    LOG(INFO) << "START RENDERING";
    cam.render(world, get_ligths());
    LOG(INFO) << "END RENDERING\n";
}

void cornell_box(RenderParameters params)
{
    hittable_list world;

    auto red = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    world.add(make_shared<quad>(point3(555, 0, 0), vec3(0, 555, 0), vec3(0, 0, 555), green));
    world.add(make_shared<quad>(point3(0, 0, 0), vec3(0, 555, 0), vec3(0, 0, 555), red));
    world.add(make_shared<quad>(point3(343, 554, 332), vec3(-130, 0, 0), vec3(0, 0, -105), light));
    world.add(make_shared<quad>(point3(0, 0, 0), vec3(555, 0, 0), vec3(0, 0, 555), white));
    world.add(make_shared<quad>(point3(555, 555, 555), vec3(-555, 0, 0), vec3(0, 0, -555), white));
    world.add(make_shared<quad>(point3(0, 0, 555), vec3(555, 0, 0), vec3(0, 555, 0), white));

    shared_ptr<hittable> box1 = box(point3(0, 0, 0), point3(165, 330, 165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265, 0, 295));
    world.add(box1);

    shared_ptr<hittable> box2 = box(point3(0, 0, 0), point3(165, 165, 165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(130, 0, 65));
    world.add(box2);

    camera cam = initialize_camera(point3(278, 278, -800), point3(278, 278, 0), params.vup, 40, params.aspect_ratio,
                                   params.image_width, params.samples_per_pixel, params.max_depth, 0, params.focus_dist,
                                   color(0, 0, 0));

    LOG(INFO) << "START RENDERING";
    cam.render(world, get_ligths());
    LOG(INFO) << "END RENDERING\n";
}

void cornell_smoke(RenderParameters params)
{
    hittable_list world;

    auto red = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(7, 7, 7));

    world.add(make_shared<quad>(point3(555, 0, 0), vec3(0, 555, 0), vec3(0, 0, 555), green));
    world.add(make_shared<quad>(point3(0, 0, 0), vec3(0, 555, 0), vec3(0, 0, 555), red));
    world.add(make_shared<quad>(point3(113, 554, 127), vec3(330, 0, 0), vec3(0, 0, 305), light));
    world.add(make_shared<quad>(point3(0, 555, 0), vec3(555, 0, 0), vec3(0, 0, 555), white));
    world.add(make_shared<quad>(point3(0, 0, 0), vec3(555, 0, 0), vec3(0, 0, 555), white));
    world.add(make_shared<quad>(point3(0, 0, 555), vec3(555, 0, 0), vec3(0, 555, 0), white));

    shared_ptr<hittable> box1 = box(point3(0, 0, 0), point3(165, 330, 165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265, 0, 295));

    shared_ptr<hittable> box2 = box(point3(0, 0, 0), point3(165, 165, 165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(130, 0, 65));

    world.add(make_shared<constant_medium>(box1, 0.01, color(0, 0, 0)));
    world.add(make_shared<constant_medium>(box2, 0.01, color(1, 1, 1)));

    camera cam = initialize_camera(point3(278, 278, -800), point3(278, 278, 0), params.vup, 40, params.aspect_ratio,
                                   params.image_width, 200, params.max_depth, 0, params.focus_dist, color(0, 0, 0));

    LOG(INFO) << "START RENDERING";
    cam.render(world, get_ligths());
    LOG(INFO) << "END RENDERING\n";
}

void final_scene(RenderParameters params)
{
    hittable_list boxes1;
    auto ground = make_shared<lambertian>(color(0.48, 0.83, 0.53));

    int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++)
    {
        for (int j = 0; j < boxes_per_side; j++)
        {
            auto w = 100.0;
            auto x0 = -1000.0 + i * w;
            auto z0 = -1000.0 + j * w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = random_double(1, 101);
            auto z1 = z0 + w;

            boxes1.add(box(point3(x0, y0, z0), point3(x1, y1, z1), ground));
        }
    }

    hittable_list world;

    world.add(make_shared<bvh_node>(boxes1));

    auto light = make_shared<diffuse_light>(color(7, 7, 7));
    world.add(make_shared<quad>(point3(123, 554, 147), vec3(300, 0, 0), vec3(0, 0, 265), light));

    auto center1 = point3(400, 400, 200);
    auto center2 = center1 + vec3(30, 0, 0);
    auto sphere_material = make_shared<lambertian>(color(0.7, 0.3, 0.1));
    world.add(make_shared<sphere>(center1, center2, 50, sphere_material));

    world.add(make_shared<sphere>(point3(260, 150, 45), 50, make_shared<dielectric>(1.5)));
    world.add(make_shared<sphere>(point3(0, 150, 145), 50, make_shared<metal>(color(0.8, 0.8, 0.9), 1.0)));

    auto boundary = make_shared<sphere>(point3(360, 150, 145), 70, make_shared<dielectric>(1.5));
    world.add(boundary);
    world.add(make_shared<constant_medium>(boundary, 0.2, color(0.2, 0.4, 0.9)));
    boundary = make_shared<sphere>(point3(0, 0, 0), 5000, make_shared<dielectric>(1.5));
    world.add(make_shared<constant_medium>(boundary, .0001, color(1, 1, 1)));

    auto emat = make_shared<lambertian>(make_shared<image_texture>("img/earthmap.jpg"));
    world.add(make_shared<sphere>(point3(400, 200, 400), 100, emat));
    auto pertext = make_shared<noise_texture>(0.1);
    world.add(make_shared<sphere>(point3(220, 280, 300), 80, make_shared<lambertian>(pertext)));

    hittable_list boxes2;
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++)
    {
        boxes2.add(make_shared<sphere>(point3::random(0, 165), 10, white));
    }

    world.add(make_shared<translate>(make_shared<rotate_y>(make_shared<bvh_node>(boxes2), 15), vec3(-100, 270, 395)));

    camera cam = initialize_camera(point3(478, 278, -600), point3(278, 278, 0), params.vup, 40, params.aspect_ratio,
                                   params.image_width, params.samples_per_pixel, params.max_depth, 0, params.focus_dist,
                                   color(0, 0, 0));

    LOG(INFO) << "START RENDERING";
    cam.render(world, get_ligths());
    LOG(INFO) << "END RENDERING\n";
}

void another_last_scene(RenderParameters params)
{
    hittable_list world;

    auto red = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    // Cornell box sides
    world.add(make_shared<quad>(point3(555, 0, 0), vec3(0, 0, 555), vec3(0, 555, 0), green));
    world.add(make_shared<quad>(point3(0, 0, 555), vec3(0, 0, -555), vec3(0, 555, 0), red));
    world.add(make_shared<quad>(point3(0, 555, 0), vec3(555, 0, 0), vec3(0, 0, 555), white));
    world.add(make_shared<quad>(point3(0, 0, 555), vec3(555, 0, 0), vec3(0, 0, -555), white));
    world.add(make_shared<quad>(point3(555, 0, 555), vec3(-555, 0, 0), vec3(0, 555, 0), white));

    // Light
    world.add(make_shared<quad>(point3(213, 554, 227), vec3(130, 0, 0), vec3(0, 0, 105), light));

    // Box
    shared_ptr<hittable> box1 = box(point3(0, 0, 0), point3(165, 330, 165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265, 0, 295));
    world.add(box1);

    // Glass Sphere
    auto glass = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(190, 90, 190), 90, glass));

    // Light Sources
    hittable_list lights;
    auto m = shared_ptr<material>();
    lights.add(make_shared<quad>(point3(343, 554, 332), vec3(-130, 0, 0), vec3(0, 0, -105), m));
    lights.add(make_shared<sphere>(point3(190, 90, 190), 90, m));

    camera cam = initialize_camera(point3(278, 278, -800), point3(278, 278, 0), params.vup, 40.0, params.aspect_ratio,
                                   params.image_width, params.samples_per_pixel, params.max_depth, params.defocus_angle,
                                   params.focus_dist, color(0, 0, 0));

    LOG(INFO) << "START RENDERING";
    cam.render(world, get_ligths());
    LOG(INFO) << "END RENDERING\n";
}

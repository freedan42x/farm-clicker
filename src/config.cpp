#include "config.hpp"

Config::Config()
{
  width = 1366;
  height = 768;
  fullscreen = true;
  fps = 60;

  plant_size = 256;
  rows = 4;
  cols = 2;

  text_size_pt = 18;
  text_line_spacing = 4;
  
  text_color = FC_MakeColor(82, 206, 255, 255);
  outline_color = FC_MakeColor(17, 83, 214, 255);
}

void Config::calculate()
{
  float aspect_ratio = (float) width / height;
  plant_hgap = width / (int) (15 * aspect_ratio);
  plant_vgap = height / (int) (10 * aspect_ratio);
  plants_per_screen = rows * cols;
  plants_total_width = plant_hgap * (rows - 1) + rows * plant_size;
  plants_total_height = plant_vgap * (cols - 1) + cols * plant_size;
  int plants_voffset = 1.1 * plant_vgap;
  plants_start_x = (width - plants_total_width) / 2;
  plants_start_y = (height - plants_total_height) / 2 - plants_voffset;

  text_size_px = (float) text_size_pt / 3 * 4;
}

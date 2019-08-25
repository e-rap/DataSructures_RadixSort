#include "RandomGenerators.h"
#include <time.h>

RandomGenerator::RandomGenerator()
  : gen{ static_cast<long unsigned int>(time(0)) }
{
  std::shuffle(names.begin(), names.end(), gen);
}

int RandomGenerator::GetRandomInt(int min, int max)
{
  std::uniform_int_distribution<int> dist(min, max);
  return dist(gen);
}

std::string RandomGenerator::GetRandomName()
{
  static int index = names.size() - 1;
  auto min{ 0 };
  auto max{ names.size() -1 };
  return names.at(GetRandomInt(min, max));
  if (index == 0)
  {
    index = names.size();
  }
  else
  {
    index--;
  }

}

std::array<std::string, 100> RandomGenerator::names = {
    "Francisco Acevedo",
     "Elaina Mcintosh",
     "Bryson Mayer",
     "Emmanuel Mullen",
     "Clare Murray",
     "Conrad Hawkins",
     "Isabell Knapp",
     "Giovanni Edwards",
     "Lewis Huerta",
     "Carsen Liu",
     "Alia Lam",
     "Luciana Monroe",
     "Laci Mcclain",
     "Addison Farley",
     "Ernest Caldwell",
     "Mathew Ball",
     "Marissa Rosario",
     "Jolie Johnston",
     "Danika Morrison",
     "Abagail Norman",
     "Skylar Villanueva",
     "Antwan Meadows",
     "Ada House",
     "Jordyn Andersen",
     "Franco Baxter",
     "Eliezer Lawson",
     "Ashlyn Stokes",
     "Francesca Walker",
     "Jamar Morales",
     "Cordell Ortega",
     "Jessie Paul",
     "Yair Jones",
     "Rebecca Owen",
     "Lyric Duarte",
     "Landin Moore",
     "Emmalee Kirby",
     "Sidney Bernard",
     "Maurice Lam",
     "Reilly Oconnell",
     "Devin Mcintyre",
     "Jaylin Farmer",
     "Dylan Krueger",
     "Layton Gonzalez",
     "Immanuel Ware",
     "Mohamed Adkins",
     "Isabel Mcknight",
     "Marvin Velez",
     "Stephany Giles",
     "Alec Dominguez",
     "Trent Newton",
     "Gabriella Cervantes",
     "Leslie Estes",
     "Luz Montgomery",
     "Nikhil Mercer",
     "Ethen Fuller",
     "Kimberly Gray",
     "Nevaeh Marquez",
     "Leon Gomez",
     "Cristopher Vasquez",
     "Amir Howard",
     "Adeline Spears",
     "Magdalena Sampson",
     "Maximillian Rice",
     "Paris Farley",
     "June Barnett",
     "Cherish Gardner",
     "Lawrence Lawrence",
     "Kenyon Landry",
     "Emilio Bautista",
     "Trinity Velez",
     "Kennedy Cooke",
     "Nia Frost",
     "Destinee Short",
     "Londyn Landry",
     "Ally Farrell",
     "Belinda Zhang",
     "Chloe Rosario",
     "Houston Huber",
     "Dwayne Mcconnell",
     "Luka Lewis",
     "Gracelyn Vaughn",
     "Zaid Williams",
     "Amber Clay",
     "Jaylynn Navarro",
     "Darien Bell",
     "Kylee Hale",
     "Wade Hurley",
     "Aniyah Garner",
     "Darion Avery",
     "Katie Leblanc",
     "Fabian Bright",
     "Jovani Steele",
     "Karly Snyder",
     "Tara Crawford",
     "Clayton Dickerson",
     "Esmeralda Gentry",
     "Ibrahim Blankenship",
     "Jacob Maxwell",
     "Ashly Brandt",
     "Ayanna Powell" };
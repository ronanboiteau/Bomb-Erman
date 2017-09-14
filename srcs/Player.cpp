#include <iostream>
#include "Empty.hh"
#include "Player.hh"
#include "ILikeToMoveIt.hpp"

Player::Player(const std::wstring &name, eColor color, Position pos, Map &map, eHeading header, size_t player, SoundManager *sound, MeshesLoader *meshesLoader, ImagesLoader *imagesLoader) :
  ACharacter(name, color, pos, map, header, player, sound, false, meshesLoader, imagesLoader)
{
  switch (player)
    {
    case 0 :
      _key.push_back(irr::KEY_KEY_Z);
      _key.push_back(irr::KEY_KEY_Q);
      _key.push_back(irr::KEY_KEY_S);
      _key.push_back(irr::KEY_KEY_D);
      _key.push_back(irr::KEY_KEY_E);
      break ;
    case 1 :
      _key.push_back(irr::KEY_KEY_T);
      _key.push_back(irr::KEY_KEY_F);
      _key.push_back(irr::KEY_KEY_G);
      _key.push_back(irr::KEY_KEY_H);
      _key.push_back(irr::KEY_KEY_Y);
      break ;
    case 2 :
      _key.push_back(irr::KEY_KEY_I);
      _key.push_back(irr::KEY_KEY_J);
      _key.push_back(irr::KEY_KEY_K);
      _key.push_back(irr::KEY_KEY_L);
      _key.push_back(irr::KEY_KEY_O);
      break ;
    case 3 :
      _key.push_back(irr::KEY_UP);
      _key.push_back(irr::KEY_LEFT);
      _key.push_back(irr::KEY_DOWN);
      _key.push_back(irr::KEY_RIGHT);
      _key.push_back(irr::KEY_RSHIFT);
      break ;
    }
  _is_AI = false;
}

Player::Player(const std::wstring &file_to_load) :
  ACharacter(file_to_load)
{
}

void	Player::Set_heading(ILikeToMoveIt const &receiver)
{
  int	i = 0;

  for (auto &it: *_characters)
    {
      if (it->Am_i_dead() == false)
	i += 1;
    }
  if (i == 1 && _is_moving != 42)
    {
      _is_moving = 42;
      _node->setMD2Animation(irr::scene::EMAT_WAVE);
    }
  else if (i != 1)
    {
      Take_bonus();
      if (receiver.IsKeyDown(_key.at(0)))
	Move(eHeading::UP);
      else if(receiver.IsKeyDown(_key.at(1)))
	Move(eHeading::LEFT);
      else if (receiver.IsKeyDown(_key.at(2)))
	Move(eHeading::DOWN);
      else if (receiver.IsKeyDown(_key.at(3)))
	Move(eHeading::RIGHT);
      else if (_is_moving != 0)
	{
	  _node->setMD2Animation(irr::scene::EMAT_STAND);
	  _is_moving = 0;
	}
      if (receiver.IsKeyDown(_key.at(4)))
	Drop_bomb();
      if (_map->Get_element(_pos)->Get_type() == BoxType::eBoxType::EXPLOSION)
	{
	  if (_extra_life == false)
	    {
	      Kill_it();
	      return ;
	    }
	  _extra_life = false;
	  _map->Set_element(Get_pos(), new Empty{Get_pos(), *_map, _meshesLoader, _imagesLoader});
	}
      _node->animateJoints();
    }
}

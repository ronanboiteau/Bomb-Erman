#ifndef BOXTYPE_HH_
# define BOXTYPE_HH_

namespace	BoxType
{
  enum class	eBoxType : size_t
    {
      BLOCK_BREAKABLE = 0,
      BLOCK_UNBREAKABLE,
      BONUS_EXTRA_LIFE,
      BONUS_MASTER_BOMB,
      BONUS_SIM_BOMB,
      BONUS_UPGRADE_RANGE,
      BONUS_LEGACY,
      BOMB_REGULAR,
      BOMB_MASTER,
      EXPLOSION,
      EMPTY
    };
};

#endif /* !BOXTYPE_HH_ */

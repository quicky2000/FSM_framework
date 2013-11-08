/*    This file is part of FSM_framework
      The aim of this software is to provided generic facilities for FSM analyzis
      Copyright (C) 2013  Julien Thevenon ( julien_thevenon at yahoo.fr )

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef POINTER_COMPARATOR_H
#define POINTER_COMPARATOR_H

namespace FSM_interfaces
{
  class FSM_situation_if;
}

namespace FSM_framework
{
  class pointer_comparator// :public std::binary_function<T*,T*,bool>
  {
  
  public:
    bool operator()(const FSM_interfaces::FSM_situation_if *p_op1,
                    const FSM_interfaces::FSM_situation_if *p_op2)const;

  private:
  
  };
}
#endif // POINTER_COMPARATOR_H 
//EOF

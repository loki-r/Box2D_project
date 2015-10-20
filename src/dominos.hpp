/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/*
 * Base code for CS 251 Software Systems Lab
 * Department of Computer Science and Engineering, IIT Bombay
 *
 */
#include <iostream>
#ifndef _DOMINOS_HPP_
#define _DOMINOS_HPP_
#define D2R 0.0174532925199432957f
#define R2D 57.295779513082320876f
namespace cs251
{
  //! This is the class that sets up the Box2D simulation world
  //! Notice the public inheritance - why do we inherit the base_sim_t class?
  class dominos_t : public base_sim_t
  {
  public:
    enum Status
    {
        on_ground,
        in_flight,
        one_jump_powerup,
        infi_jump_powerup,
        rocket_powerup,
        rocket_powerup_on,
    };
    Status status;
    bool game_over;
    int t;
    bool one_jump,infi_jump,hit_tri,jetpack,fieldrod;
    b2Body *trunk,*hand1,*hand2,*leg1,*leg2,*field,*gameoverbody;
    dominos_t();
    b2Body* b1;
    b2Body* gd;
    b2Body* gd3;
    b2Body* b2;
    b2Body* gd1;
    b2Body* b3;
    b2Body* b4;
    b2Body* b5;
    b2Body* b6;
    b2Body* gd2;
    b2Body* b7;
    b2Body* b8;
    b2Body* b9;
    b2Body* b10;
    b2Body* spherebody;
    b2Body* b11;
    b2Body* b12;
    b2Body* b13_1;
    b2Body* b13_2;
    b2Body* gd_2;
    b2Body* b13_3;
    b2Body* b13_4;
    b2Body* b14_1;
    b2Body* b14_2;
    b2Body* b14_3;
    b2Body* b14_4;
    debug_draw_t m_debug_draw;

      void keyboard(unsigned char key)
        {
       /*! keyboard
        * \brief This function takes input from the keyboard and does the required action.
        */
            switch (key)
            {
              case ' ': //move up
              if(status == on_ground)
               {     b2Vec2 vel = trunk->GetLinearVelocity();
                    vel.y = 10;//upwards
                    vel.x=1;
                    trunk->SetLinearVelocity( vel );
                    hand1->SetLinearVelocity( vel );
                    hand2->SetLinearVelocity( vel );
                    leg1->SetLinearVelocity( vel );
                    leg2->SetLinearVelocity( vel );
                }
              if(status == one_jump_powerup)
               {     b2Vec2 vel = trunk->GetLinearVelocity();
                    vel.y = 10;//upwards
                    vel.x=3;
                    trunk->SetLinearVelocity( vel );
                    hand1->SetLinearVelocity( vel );
                    hand2->SetLinearVelocity( vel );
                    leg1->SetLinearVelocity( vel );
                    leg2->SetLinearVelocity( vel );
                    status = in_flight;
                }
              if(status == infi_jump_powerup)
               {     b2Vec2 vel = trunk->GetLinearVelocity();
                    vel.y = 10;//upwards
                    vel.x=3;
                    trunk->SetLinearVelocity( vel );
                    hand1->SetLinearVelocity( vel );
                    hand2->SetLinearVelocity( vel );
                    leg1->SetLinearVelocity( vel );
                    leg2->SetLinearVelocity( vel );
                }
                if(status == rocket_powerup_on)
               {
                    // std::cout<<"status == rocket_powerup_on"<<std::endl;
                    m_world->SetGravity( b2Vec2(0,-10) );
                    status = rocket_powerup;
                    return;
                }
              if(status == rocket_powerup)
               {
                    // std::cout<<"status == rocket_powerup"<<std::endl;
                    m_world->SetGravity( b2Vec2(0,10) );
                    status = rocket_powerup_on;

                }

                    break;
              default:
                //run default behaviour
                base_sim_t::keyboard(key);
            }
        }

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
    {
      // std::cout<<"lol1"<<std::endl;
       /*! PreSolve
        * \brief This function is called before any two bodies collide. This function helps in deleting the power up's when they are hit.
        */
      base_sim_t::PreSolve(contact, oldManifold);
      b2Body* body1 = contact->GetFixtureA()->GetBody();
      b2Body* body2 = contact->GetFixtureB()->GetBody();
      if( ( (body1 == leg1 || body1 == leg2 || body1 == trunk || body1 == hand1 || body1 == hand2) && body2 == gd3 )
       || ( (body2 == leg1 || body2 == leg2 || body2 == trunk || body2 == hand1 || body2 == hand2) && body1 == gd3 ) )
      {
        contact->SetEnabled(false);
        one_jump = true;
        status = one_jump_powerup;
      }
      if( ( (body1 == leg1 || body1 == leg2 || body1 == trunk || body1 == hand1 || body1 == hand2) && body2 == gd1 )
       || ( (body2 == leg1 || body2 == leg2 || body2 == trunk || body2 == hand1 || body2 == hand2) && body1 == gd1 ) )
      {
        contact->SetEnabled(false);
        infi_jump = true;
        status = infi_jump_powerup;
      }

      if( ( (body1 == leg1 || body1 == leg2 || body1 == trunk || body1 == hand1 || body1 == hand2) && body2 == gd )
       || ( (body2 == leg1 || body2 == leg2 || body2 == trunk || body2 == hand1 || body2 == hand2) && body1 == gd )
       || ( (body1 == leg1 || body1 == leg2 || body1 == trunk || body1 == hand1 || body1 == hand2) && body2 == gd_2 )
       || ( (body2 == leg1 || body2 == leg2 || body2 == trunk || body2 == hand1 || body2 == hand2) && body1 == gd_2 ))
      {
        contact->SetEnabled(false);
        hit_tri = true;
      }
      if( ( (body1 == leg1 || body1 == leg2 || body1 == trunk || body1 == hand1 || body1 == hand2) && body2 == gd2 )
       || ( (body2 == leg1 || body2 == leg2 || body2 == trunk || body2 == hand1 || body2 == hand2) && body1 == gd2 ) )
      {
        contact->SetEnabled(false);
        jetpack = true;
        status = rocket_powerup;
        // m_world->SetGravity( b2Vec2(0,10) );
      }
      if( ( (body1 == leg1 || body1 == leg2 || body1 == trunk || body1 == hand1 || body1 == hand2) && body2 == spherebody )
       || ( (body2 == leg1 || body2 == leg2 || body2 == trunk || body2 == hand1 || body2 == hand2) && body1 == spherebody ) )
      {
        contact->SetEnabled(false);
        fieldrod = true;
      }

    }

    void BeginContact(b2Contact* contact)
    {
       /*! BeginContact
        * \brief This function is called after any two bodies start contact. This function helps in changing the status variable which gives where the man is.
        */
        b2Body* body1 = contact->GetFixtureA()->GetBody();
        b2Body* body2 = contact->GetFixtureB()->GetBody();
        int a=(body1->GetIntData());
        int b=(body2->GetIntData());


    if(b==200){game_over=true;t++;}

        bool ground_check;
        ground_check = ( ( (body1 == leg1 || body1 == leg2) && body2 == b1 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b1 ) )
        || ( ( (body1 == leg1 || body1 == leg2) && body2 == b2 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b2 ) )
        || ( ( (body1 == leg1 || body1 == leg2) && body2 == b3 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b3 ) )
        || ( ( (body1 == leg1 || body1 == leg2) && body2 == b5 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b5 ) )
        || ( ( (body1 == leg1 || body1 == leg2) && body2 == b7 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b7 ) )
        || ( ( (body1 == leg1 || body1 == leg2) && body2 == b9 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b9 ) )
        || ( ( (body1 == leg1 || body1 == leg2) && body2 == b11 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b11 ) )
        || ( ( (body1 == leg1 || body1 == leg2) && body2 == b13_1 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b13_1 ) );


        if( ground_check )
        {
          status = on_ground;
          m_world->SetGravity( b2Vec2(0,-10) );
        }
        if(a!=12){ if(b!=12){return;}b=a;a=12;}
        if(b==0){return;}
    }

    void EndContact(b2Contact* contact)
    {
       /*! BeginContact
        * \brief This function is called after any two bodies end to contact. This function helps in changing the status variable which gives where the man is.
        */
        b2Body* body1 = contact->GetFixtureA()->GetBody();
        b2Body* body2 = contact->GetFixtureB()->GetBody();

        bool ground_check;
        ground_check = ( ( (body1 == leg1 || body1 == leg2) && body2 == b1 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b1 ) )
        || ( ( (body1 == leg1 || body1 == leg2) && body2 == b2 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b2 ) )
        || ( ( (body1 == leg1 || body1 == leg2) && body2 == b3 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b3 ) )
        || ( ( (body1 == leg1 || body1 == leg2) && body2 == b5 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b5 ) )
        || ( ( (body1 == leg1 || body1 == leg2) && body2 == b7 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b7 ) )
        || ( ( (body1 == leg1 || body1 == leg2) && body2 == b9 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b9 ) )
        || ( ( (body1 == leg1 || body1 == leg2) && body2 == b11 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b11 ) )
        || ( ( (body1 == leg1 || body1 == leg2) && body2 == b13_1 ) || ( (body2 == leg1 || body2 == leg2) && body1 == b13_1 ) );
        if( ground_check )
        {
          status = in_flight;
        }
    }

    void step(settings_t* settings)
    {
       /*! step
        * \brief This function is called during every step. This function helps in destroying the power up's and man when required.
        */
        base_sim_t::step(settings);
        if(one_jump)
        {
            m_world->DestroyBody(gd3);
            one_jump = false;
        }
        if(infi_jump)
        {
            m_world->DestroyBody(gd1);
            infi_jump = false;
        }
        if(hit_tri)
        {
            m_world->DestroyBody(leg1);
            m_world->DestroyBody(leg2);
            m_world->DestroyBody(hand1);
            m_world->DestroyBody(hand2);
            m_world->DestroyBody(trunk);
            hit_tri = false;
        }
        if(jetpack)
        {
            m_world->DestroyBody(gd2);
            jetpack = false;
        }
        if(fieldrod)
        {
            m_world->DestroyBody(spherebody);
            m_world->DestroyBody(field);
            fieldrod = false;
        }
        if(game_over)
     {
      m_debug_draw.DrawString(5, m_text_line, "****************GAME OVER****************");
      for ( b2Body* b = m_world->GetBodyList(); b;)
       {
          b2Body* c=b->GetNext();
          m_world->DestroyBody(b);
          b=c;
       }
     }

    }

    static base_sim_t* create()
    {
      return new dominos_t;
    }
  };
}

#endif

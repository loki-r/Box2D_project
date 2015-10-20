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


#include "cs251_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs251
{
  /**  The is the constructor
   * This is the documentation block for the constructor.
   */

  dominos_t::dominos_t()
  {
    //Ground

    one_jump = false;
    infi_jump = false;
    hit_tri = false;
    jetpack = false;
    fieldrod = false;
    game_over = false;
    m_world->SetGravity( b2Vec2(0,-10) );
    /*! b1
     * \brief pointer to the body ground
     */
     int gv=-4;

    {

       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,-12.0f);
       a[1]=b2Vec2(32.0f,-12.0f);
       a[2]=b2Vec2(32.0f,0.0f);
       a[3]=b2Vec2(0.0f,0.0f);
      shape.Set(a,4);
      b2BodyDef bd;
      int i=0;
      bd.type=b2_kinematicBody;
      bd.position.Set(-55.0f, 8.0f);
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
      b1->SetLinearVelocity(b2Vec2(gv,0));
      b1->SetIntData(i);
    }
    //the trinagular obstrucle
    /*! gd
     * \brief pointer to the triangle obstrucle.If the man hits this obstacle game is over.
     */

    {
     b2PolygonShape shape;
     b2Vec2* a = new b2Vec2[3];
     a[0]=b2Vec2(-1.0f,0.0f);
     a[1]=b2Vec2(0.0f,2.0f);
     a[2]=b2Vec2(1.0f,0.0f);
     shape.Set(a,3);
     for(int i=0;i<2;i++)
     {
     b2BodyDef bd;
     bd.type=b2_kinematicBody;
     int j=200;

     bd.position.Set(-28.5f + 2.0f * i, 8.0f);
     gd = m_world->CreateBody(&bd);

     gd->CreateFixture(&shape,0.0f);
     gd->SetLinearVelocity(b2Vec2(gv,0));
     gd->SetIntData(j);
     }

     for(int i=0;i<2;i++)
     {
     b2BodyDef bd;
     bd.type=b2_kinematicBody;
     int j=200;

     bd.position.Set(-10.0f + 9.0f * i, 13.0f);
     gd = m_world->CreateBody(&bd);
     gd->CreateFixture(&shape,0.0f);
     gd->SetLinearVelocity(b2Vec2(gv,0));
     gd->SetIntData(j);
     }
    }

     //square powerup
    /*! gd3
     * \brief pointer to the square power up.If the man takes this power up, he will get a jump in air.
     */


    {
     b2PolygonShape shape;
     b2Vec2* a = new b2Vec2[4];
     a[1]=b2Vec2(-0.5f,0.5f);
     a[0]=b2Vec2(0.5f,0.5f);
     a[3]=b2Vec2(-0.5f,-0.5f);
     a[2]=b2Vec2(0.5f,-0.5f);
     shape.Set(a,4);
     int i=2;
     b2BodyDef bd;
     bd.type=b2_kinematicBody;
     bd.position.Set(-17.0f, 15.5f);
     gd3 = m_world->CreateBody(&bd);
     gd3->CreateFixture(&shape,0.0f);
     gd3->SetLinearVelocity(b2Vec2(gv,0));
     gd3->SetIntData(i);
    }

    /*! b2
     * \brief pointer to the ground object. If he lands on this object, hi will lose any kind of power up. If he misses this ground he will die.
     */


    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,-17.0f);
       a[1]=b2Vec2(11.0f,-17.0f);
       a[2]=b2Vec2(11.0f,0.0f);
       a[3]=b2Vec2(0.0f,0.0f);
      shape.Set(a,4);
      b2BodyDef bd;
      int i=0;
      bd.type=b2_kinematicBody;
      bd.position.Set(-11.0f, 13.0f);
      b2 = m_world->CreateBody(&bd);
      b2->CreateFixture(&shape, 0.0f);
      b2->SetLinearVelocity(b2Vec2(gv,0));
      b2->SetIntData(i);
    }

    //rhombus shape
    /*! gd1
     * \brief pointer to the rhombus power up.If the man takes this power up, he will get infinte number of jumps in air.
     */

    {
     b2PolygonShape shape;
     b2Vec2* a = new b2Vec2[4];
     a[0]=b2Vec2(-1.0f,1.0f);
     a[1]=b2Vec2(0.0f,2.0f);
     a[2]=b2Vec2(1.0f,1.0f);
     a[3]=b2Vec2(0.0f,0.0f);
     shape.Set(a,4);
     int i=3;
     b2BodyDef bd;
     bd.type=b2_kinematicBody;
     bd.position.Set(5.0f, 15.5f);
     gd1 = m_world->CreateBody(&bd);
     gd1->CreateFixture(&shape,0.0f);
     gd1->SetLinearVelocity(b2Vec2(gv,0));
     gd1->SetIntData(i);
    }
    /*! b3
     * \brief pointer to the ground object. If he lands on this object, hi will lose any kind of power up. If he misses this ground he will die.
     */

    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,-12.0f);
       a[1]=b2Vec2(3.5f,-12.0f);
       a[2]=b2Vec2(3.5f,0.0f);
       a[3]=b2Vec2(0.0f,0.0f);
      shape.Set(a,4);
      b2BodyDef bd;
      int i=0;
      bd.position.Set(12.0f, 8.0f);
       bd.type=b2_kinematicBody;
      b3 = m_world->CreateBody(&bd);
      b3->CreateFixture(&shape, 0.0f);
      b3->SetLinearVelocity(b2Vec2(gv,0));
      b3->SetIntData(i);
    }
    /*! b4
     * \brief pointer to the roof object. If he hits this object, hi doesn't lose any kind of power up.
     */

    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,52.0f);
       a[1]=b2Vec2(3.5f,52.0f);
       a[2]=b2Vec2(3.5f,0.0f);
       a[3]=b2Vec2(0.0f,0.0f);
      shape.Set(a,4);
      int i=100;
      b2BodyDef bd;
      bd.position.Set(12.0f, 20.0f);
       bd.type=b2_kinematicBody;
      b4 = m_world->CreateBody(&bd);
      b4->CreateFixture(&shape, 0.0f);
      b4->SetLinearVelocity(b2Vec2(gv,0));
      b4->SetIntData(i);
    }
    /*! b5
     * \brief pointer to the ground object. If he lands on this object, hi will lose any kind of power up. If he misses this ground he will die.
     */

    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,-9.0f);
       a[1]=b2Vec2(3.5f,-9.0f);
       a[2]=b2Vec2(3.5f,0.0f);
       a[3]=b2Vec2(0.0f,0.0f);
      shape.Set(a,4);
      int i=0;
      b2BodyDef bd;
      bd.position.Set(22.0f, 5.0f);
       bd.type=b2_kinematicBody;
      b5 = m_world->CreateBody(&bd);
      b5->CreateFixture(&shape, 0.0f);
      b5->SetLinearVelocity(b2Vec2(gv,0));
      b5->SetIntData(i);
    }
    /*! b6
     * \brief pointer to the roof object. If he hits this object, hi doesn't lose any kind of power up.
     */

    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,52.0f);
       a[1]=b2Vec2(3.5f,52.0f);
       a[2]=b2Vec2(3.5f,0.0f);
       a[3]=b2Vec2(0.0f,0.0f);
      shape.Set(a,4);
      int i=100;
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(22.0f, 15.5f);
      b6 = m_world->CreateBody(&bd);
      b6->CreateFixture(&shape, 0.0f);
      b6->SetLinearVelocity(b2Vec2(gv,0));
      b6->SetIntData(i);
    }


    //rocket powerup
    /*! gd2
     * \brief pointer to the rocket power up.If the man takes this power up, he can fly. Use space bar to turn in on and off.
     */

    {
     b2PolygonShape shape;
     b2Vec2* a = new b2Vec2[4];
     a[1]=b2Vec2(-0.8f,0.8f);
     a[0]=b2Vec2(0.0f,0.0f);
     a[3]=b2Vec2(1.5f,1.5f);
     a[2]=b2Vec2(0.7f,2.3f);
     shape.Set(a,4);
     int i=4;
     b2BodyDef bd;
     bd.type=b2_kinematicBody;
     bd.position.Set(30.0f, 12.0f);
     gd2 = m_world->CreateBody(&bd);
     gd2->CreateFixture(&shape,0.0f);
     gd2->SetLinearVelocity(b2Vec2(gv,0));
     gd2->SetIntData(i);
    }

    /*! b7
     * \brief pointer to the ground object. If he lands on this object, hi will lose any kind of power up. If he misses this ground he will die.
     */
    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,-10.5f);
       a[1]=b2Vec2(3.5f,-10.5f);
       a[2]=b2Vec2(3.5f,0.0f);
       a[3]=b2Vec2(0.0f,0.0f);
      shape.Set(a,4);
      int i=0;
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(45.0f, 6.5f);
      b7 = m_world->CreateBody(&bd);
      b7->CreateFixture(&shape, 0.0f);
      b7->SetLinearVelocity(b2Vec2(gv,0));
      b7->SetIntData(i);
    }
    /*! b8
     * \brief pointer to the roof object. If he hits this object, hi doesn't lose any kind of power up.
     */

    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,52.0f);
       a[1]=b2Vec2(3.5f,52.0f);
       a[2]=b2Vec2(3.5f,0.0f);
       a[3]=b2Vec2(0.0f,0.0f);
      shape.Set(a,4);
      int i=100;
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(45.0f, 21.5f);
      b8 = m_world->CreateBody(&bd);
      b8->CreateFixture(&shape, 0.0f);
      b8->SetLinearVelocity(b2Vec2(gv,0));
      b8->SetIntData(i);
    }

    /*! b9
     * \brief pointer to the ground object. If he lands on this object, hi will lose any kind of power up. If he misses this ground he will die.
     */
    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,-7.5f);
       a[1]=b2Vec2(3.5f,-7.5f);
       a[2]=b2Vec2(3.5f,0.0f);
       a[3]=b2Vec2(0.0f,0.0f);
      shape.Set(a,4);
      int i=0;
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(54.0f, 3.5f);
      b9 = m_world->CreateBody(&bd);
      b9->CreateFixture(&shape, 0.0f);
      b9->SetLinearVelocity(b2Vec2(gv,0));
      b9->SetIntData(i);
    }

    /*! b10
     * \brief pointer to the roof object. If he hits this object, hi doesn't lose any kind of power up.
     */
    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,52.0f);
       a[1]=b2Vec2(3.5f,52.0f);
       a[2]=b2Vec2(3.5f,0.0f);
       a[3]=b2Vec2(0.0f,0.0f);
      shape.Set(a,4);
      int i=100;
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(54.0f, 18.5f);
      b10 = m_world->CreateBody(&bd);
      b10->CreateFixture(&shape, 0.0f);
      b10->SetLinearVelocity(b2Vec2(gv,0));
      b1->SetIntData(i);
    }

    /*! spherebody
     * \brief pointer to the spherical object. If the man takes this, the rod like obstacle which doesn't allow him to go further, will be  removed.
     */

     {
      b2CircleShape circle;
      int i=5;
      circle.m_radius = 1.0;
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
    b2BodyDef ballbd;
    ballbd.type = b2_kinematicBody;
    ballbd.position.Set(64.0f, 18.0f);
    spherebody = m_world->CreateBody(&ballbd);
    spherebody->CreateFixture(&ballfd);
    spherebody->SetLinearVelocity(b2Vec2(gv,0));
    spherebody->SetIntData(i);
  }
    /*! field
     * \brief pointer to the rod like obstacle which doesn't allow the man to go further object.
     */
{
      b2PolygonShape shape;
      shape.SetAsBox(0.1,7.5);
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(70.0f, 21.0f);
      field = m_world->CreateBody(&bd);
      field->CreateFixture(&shape, 0.0f);
      field->SetLinearVelocity(b2Vec2(gv,0));
    }


    /*! b11
     * \brief pointer to the ground object. If he lands on this object, hi will lose any kind of power up. If he misses this ground he will die.
     */

    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,-17.5f);
       a[1]=b2Vec2(3.5f,-17.5f);
       a[2]=b2Vec2(3.5f,0.0f);
       a[3]=b2Vec2(0.0f,0.0f);
      shape.Set(a,4);
      int i=0;
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(70.0f, 13.5f);
      b11 = m_world->CreateBody(&bd);
      b11->CreateFixture(&shape, 0.0f);
      b11->SetLinearVelocity(b2Vec2(gv,0));
      b11->SetIntData(i);
    }

    /*! b12
     * \brief pointer to the roof object. If he hits this object, hi doesn't lose any kind of power up.
     */
    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,52.0f);
       a[1]=b2Vec2(3.5f,52.0f);
       a[2]=b2Vec2(3.5f,0.0f);
       a[3]=b2Vec2(0.0f,0.0f);
      shape.Set(a,4);
      int i=100;
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(70.0f, 28.5f);
      b12 = m_world->CreateBody(&bd);
      b12->CreateFixture(&shape, 0.0f);
      b12->SetLinearVelocity(b2Vec2(gv,0));
      b12->SetIntData(i);
    }
    /*! b13_1
     * \brief pointer to the ground object. If he lands on this object, hi will lose any kind of power up. If he misses this ground he will die.
     */

    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,0.0f);
       a[1]=b2Vec2(0.0f,-21.0f);
       a[2]=b2Vec2(9.0f,-21.0f);
       a[3]=b2Vec2(9.0f,0.0f);
      shape.Set(a,4);
      int i=0;
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(85.0f, 17.0f);
      b13_1 = m_world->CreateBody(&bd);
      b13_1->CreateFixture(&shape, 0.0f);
      b13_1->SetLinearVelocity(b2Vec2(gv,0));
      b13_1->SetIntData(i);
    }
    /*! b13_2
     * \brief pointer to the ground object. If he lands on this object, hi will lose any kind of power up. If he misses this ground he will die.
     */

    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,0.0f);
       a[1]=b2Vec2(0.0f,-25.0f);
       a[2]=b2Vec2(9.0f,-25.0f);
       a[3]=b2Vec2(9.0f,0.0f);
      shape.Set(a,4);
      int i=0;
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(94.0f, 21.0f);
      b13_2 = m_world->CreateBody(&bd);
      b13_2->CreateFixture(&shape, 0.0f);
      b13_2->SetLinearVelocity(b2Vec2(gv,0));
      b13_2->SetIntData(i);
    }

    /*! gd_2
     * \brief pointer to the triangle obstrucle.If the man hits this obstacle game is over.
     */
    {
     b2PolygonShape shape;
     b2Vec2* a = new b2Vec2[3];
     a[0]=b2Vec2(-1.0f,0.0f);
     a[1]=b2Vec2(0.0f,2.0f);
     a[2]=b2Vec2(1.0f,0.0f);
     shape.Set(a,3);
     int j=200;
     for(int i=0;i<4;i++)
     {
     b2BodyDef bd;
     bd.type=b2_kinematicBody;
     bd.position.Set(95.0f + 2.0f * i, 21.0f);
     gd_2 = m_world->CreateBody(&bd);
     gd_2->CreateFixture(&shape,0.0f);
     gd_2->SetLinearVelocity(b2Vec2(gv,0));
     }

     for(int i=0;i<4;i++)
     {
     b2BodyDef bd;
     bd.type=b2_kinematicBody;
     bd.position.Set(104.0f + 2.0f * i, 25.0f);
     gd_2 = m_world->CreateBody(&bd);
     gd_2->CreateFixture(&shape,0.0f);
     gd_2->SetLinearVelocity(b2Vec2(gv,0));
     }

     for(int i=0;i<11;i++)
     {
     b2BodyDef bd;
     bd.type=b2_kinematicBody;
     bd.position.Set(113.0f + 2.0f * i, 29.0f);
     gd_2 = m_world->CreateBody(&bd);
     gd_2->CreateFixture(&shape,0.0f);
     gd_2->SetLinearVelocity(b2Vec2(gv,0));
     }
     gd_2->SetIntData(j);
    }

    /*! b13_4
     * \brief pointer to the ground object. If he lands on this object, hi will lose any kind of power up. If he misses this ground he will die.
     */
    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,0.0f);
       a[1]=b2Vec2(0.0f,-29.0f);
       a[2]=b2Vec2(9.0f,-29.0f);
       a[3]=b2Vec2(9.0f,0.0f);
      shape.Set(a,4);
      int i=0;
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(103.0f, 25.0f);
      b13_3 = m_world->CreateBody(&bd);
      b13_3->CreateFixture(&shape, 0.0f);
      b13_3->SetLinearVelocity(b2Vec2(gv,0));
      b13_3->SetIntData(i);
    }
    /*! b13_4
     * \brief pointer to the ground object. If he lands on this object, hi will lose any kind of power up. If he misses this ground he will die.
     */

    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,0.0f);
       a[1]=b2Vec2(0.0f,-33.0f);
       a[2]=b2Vec2(22.0f,-33.0f);
       a[3]=b2Vec2(22.0f,0.0f);
      shape.Set(a,4);
      int i=0;
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(112.0f, 29.0f);

      b13_4 = m_world->CreateBody(&bd);
      b13_4->CreateFixture(&shape, 0.0f);
      b13_4->SetLinearVelocity(b2Vec2(gv,0));
      b13_4->SetIntData(i);
    }

    /*! b14_1
     * \brief pointer to the roof object. If he hits this object, hi doesn't lose any kind of power up.
     */
    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,52.0f);
       a[1]=b2Vec2(9.0f,52.0f);
       a[2]=b2Vec2(9.0f,0.0f);
       a[3]=b2Vec2(0.0f,0.0f);
      shape.Set(a,4);
      int i=100;
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(85.0f, 34.0f);
      b14_1 = m_world->CreateBody(&bd);
      b14_1->CreateFixture(&shape, 0.0f);
      b14_1->SetLinearVelocity(b2Vec2(gv,0));
      b14_1->SetIntData(i);
    }

    /*! b14_2
     * \brief pointer to the roof object. If he hits this object, hi doesn't lose any kind of power up.
     */

    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,0.0f);
       a[1]=b2Vec2(0.0f,52.0f);
       a[2]=b2Vec2(9.0f,52.0f);
       a[3]=b2Vec2(9.0f,0.0f);
      shape.Set(a,4);
      int i=100;
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(94.0f, 39.0f);
      b14_2 = m_world->CreateBody(&bd);
      b14_2->CreateFixture(&shape, 0.0f);
      b14_2->SetLinearVelocity(b2Vec2(gv,0));
      b14_2->SetIntData(i);
    }

    /*! b14_3
     * \brief pointer to the roof object. If he hits this object, hi doesn't lose any kind of power up.
     */
    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,0.0f);
       a[1]=b2Vec2(0.0f,52.0f);
       a[2]=b2Vec2(9.0f,52.0f);
       a[3]=b2Vec2(9.0f,0.0f);
      shape.Set(a,4);
      int i=100;
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(103.0f, 43.0f);
      b14_3 = m_world->CreateBody(&bd);
      b14_3->CreateFixture(&shape, 0.0f);
      b14_3->SetLinearVelocity(b2Vec2(gv,0));
      b14_3->SetIntData(i);
    }
    /*! b14_4
     * \brief pointer to the roof object. If he hits this object, hi doesn't lose any kind of power up.
     */

    {
       b2PolygonShape shape;
       b2Vec2* a = new b2Vec2[4];
       a[0]=b2Vec2(0.0f,0.0f);
       a[1]=b2Vec2(0.0f,52.0f);
       a[2]=b2Vec2(22.0f,52.0f);
       a[3]=b2Vec2(22.0f,0.0f);
      shape.Set(a,4);
      int i=100;
      b2BodyDef bd;
       bd.type=b2_kinematicBody;
      bd.position.Set(112.0f, 45.0f);
      b14_4 = m_world->CreateBody(&bd);
      b14_4->CreateFixture(&shape, 0.0f);
      b14_4->SetLinearVelocity(b2Vec2(gv,0));
      b14_4->SetIntData(i);
    }




    {
    b2BodyDef bodydef;
    int i=12;
    bodydef.type = b2_dynamicBody;
    bodydef.position.Set(-37, 16);
    trunk = m_world->CreateBody(&bodydef);
    b2PolygonShape shape;
    shape.SetAsBox(1, 1);
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &shape;
    //myFixtureDef.density = 0;
       /*! trunk
        * \brief pointer to the body without legs and arms.
        */
    trunk->CreateFixture(&myFixtureDef);
    trunk->SetIntData(i);
    b2Vec2 vertices[4];
    vertices[0].Set(0.7, -1);
    vertices[1].Set(-0.7,  -1);
    vertices[2].Set( -0.7, -5);
    vertices[3].Set( 0.7, -5);
    b2PolygonShape polygonShape;
    polygonShape.Set(vertices, 4);
    myFixtureDef.shape = &polygonShape;
    //myFixtureDef.density = 0;
    trunk->CreateFixture(&myFixtureDef);
    //hand1
       /*! hand1
        * \brief pointer to one of the hands.
        */
    bodydef.position.Set(-0.707106781186548-37, -1.5-0.707106781186548+16);
    bodydef.angle = -45 * D2R;
    hand1 = m_world->CreateBody(&bodydef);
    shape.SetAsBox(0.35, 1.5);
    myFixtureDef.shape = &shape;
    myFixtureDef.density = 0;
    hand1->CreateFixture(&myFixtureDef);
    hand1->SetIntData(i);
    b2RevoluteJointDef revoluteJointDef;
    revoluteJointDef.bodyA = trunk;
    revoluteJointDef.bodyB = hand1;
    revoluteJointDef.collideConnected = false;
    revoluteJointDef.localAnchorA.Set(0,-1.5);
    revoluteJointDef.localAnchorB.Set(0,1);
    m_world->CreateJoint( &revoluteJointDef );
    //hand2
       /*! hand2
        * \brief pointer to one of the hands.
        */
    bodydef.position.Set(0.707106781186548-37, -1.5-0.707106781186548+16);
    bodydef.angle = 45 * D2R;
    hand2 = m_world->CreateBody(&bodydef);
    shape.SetAsBox(0.35, 1.5);
    myFixtureDef.shape = &shape;
    myFixtureDef.density = 0;
    hand2->CreateFixture(&myFixtureDef);
    hand2->SetIntData(i);
    b2RevoluteJointDef revoluteJointDef2;
    revoluteJointDef2.bodyA = trunk;
    revoluteJointDef2.bodyB = hand2;
    revoluteJointDef2.collideConnected = false;
    revoluteJointDef2.localAnchorA.Set(0,-1.5);
    revoluteJointDef2.localAnchorB.Set(0,1);
    m_world->CreateJoint( &revoluteJointDef2 );

    b2RevoluteJointDef revoluteJointDef3;
    revoluteJointDef3.bodyA = hand1;
    revoluteJointDef3.bodyB = hand2;
    revoluteJointDef3.collideConnected = false;
    revoluteJointDef3.localAnchorA.Set(0,1);
    revoluteJointDef3.localAnchorB.Set(0,1);
    m_world->CreateJoint( &revoluteJointDef3 );
    //leg1
       /*! leg1
        * \brief pointer to one of the legs.
        */
    bodydef.position.Set(-0.707106781186548-37, -4.5-0.707106781186548+16-0.4);
    bodydef.angle = -45 * D2R;
    leg1 = m_world->CreateBody(&bodydef);
    shape.SetAsBox(0.35, 1.5);
    myFixtureDef.shape = &shape;
    myFixtureDef.density = 0;
    leg1->CreateFixture(&myFixtureDef);
    leg1->SetIntData(i);
    b2RevoluteJointDef revoluteJointDef4;
    revoluteJointDef4.bodyA = trunk;
    revoluteJointDef4.bodyB = leg1;
    revoluteJointDef4.collideConnected = false;
    revoluteJointDef4.localAnchorA.Set(0,-4.5-0.4);
    revoluteJointDef4.localAnchorB.Set(0,1);
    m_world->CreateJoint( &revoluteJointDef4 );
     //leg2
       /*! leg2
        * \brief pointer to one of the legs.
        */
    bodydef.position.Set(0.707106781186548-37, -4.5-0.707106781186548+16-0.4);
    bodydef.angle = 45 * D2R;
    leg2 = m_world->CreateBody(&bodydef);
    shape.SetAsBox(0.35, 1.5);
    myFixtureDef.shape = &shape;
    myFixtureDef.density = 0;
    leg2->CreateFixture(&myFixtureDef);
    leg2->SetIntData(i);
    b2RevoluteJointDef revoluteJointDef5;
    revoluteJointDef5.bodyA = trunk;
    revoluteJointDef5.bodyB = leg2;
    revoluteJointDef5.collideConnected = false;
    revoluteJointDef5.localAnchorA.Set(0,-4.5-0.4);
    revoluteJointDef5.localAnchorB.Set(0,1);
    m_world->CreateJoint( &revoluteJointDef5 );

    b2RevoluteJointDef revoluteJointDef6;
    revoluteJointDef6.bodyA = leg1;
    revoluteJointDef6.bodyB = leg2;
    revoluteJointDef6.collideConnected = false;
    revoluteJointDef6.localAnchorA.Set(0,1);
    revoluteJointDef6.localAnchorB.Set(0,1);
    m_world->CreateJoint( &revoluteJointDef6 );
    }

    b2Vec2 vel ;
  vel.y = 10;//upwards
    vel.x=3;
    trunk->SetLinearVelocity( vel );
    hand1->SetLinearVelocity( vel );
    hand2->SetLinearVelocity( vel );
    leg1->SetLinearVelocity( vel );
    leg2->SetLinearVelocity( vel );
    status = in_flight;

    ////////////////////////////////////////////////
       /*! gameoverbody
        * \brief pointer to the thin rod like body, below all the game bodies. If the player hits this the game is over.
        */
    {
       b2PolygonShape shape;
      shape.SetAsBox(150.0f,0.1f);
      b2BodyDef bd;
      int i=200;
       bd.type=b2_kinematicBody;
      bd.position.Set(55.0f,-5.0f);
      gameoverbody = m_world->CreateBody(&bd);
      gameoverbody->CreateFixture(&shape, 0.0f);
      gameoverbody->SetLinearVelocity(b2Vec2(gv,0));
      gameoverbody->SetIntData(i);
    }

  }


  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}

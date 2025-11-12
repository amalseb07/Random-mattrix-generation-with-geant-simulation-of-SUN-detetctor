////////////////////////////////////////////////////////////////////////////////////////////
// Author: Steve Quinn                                                                    //
//                                                                                        //
// Description: This is the file where the SuN detector is built. You can follow the      //
//   syntax below to build and place your own detectors. There is also many useful        //
//   examples online.                                                                     //
//                                                                                        //
// Steps: 1. Define the elements that you need                                            //
//        2. Use these elements to define the materials for the experimental setup        //
//        3. Create an experimental room of air, vacuum, etc.                             //
//        4. Create your experimental setup and place it in the experimental room         //
//        5. Apply the color scheme you want for the optional visualization               //
//                                                                                        //
// Important: The way the code is currently set up, you are required to fill the array    //
//   called detectorName[i] with the name of the detectors you want to save in your       //
//   ROOT file.  In this example the names are "Det1" and "Det2" (see syntax below).      //
////////////////////////////////////////////////////////////////////////////////////////////

#include "DetectorConstruction.hh"
#include "G4SDManager.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include <iostream>
#include <sstream>
#include "G4String.hh"
#include "G4ios.hh"
#include <stdio.h>

DetectorConstruction::DetectorConstruction()
  :  NaI(0), Al(0), N78O21Ar1(0), Cr20Ni8Fe76(0), C2F4(0), C5O2H8(0)
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  DefineMaterials();

  return ConstructDetector();
}

void DetectorConstruction::DefineMaterials()
{

  // define Parameters
     G4String name, symbol;  
     G4double a, z, density;           
     G4int ncomponents, natoms;

  // define Elements

     a = 22.99*g/mole;
     G4Element* Na = new G4Element(name="Sodium" ,symbol="Na" , z= 11., a);

     a = 126.90*g/mole;
     G4Element* I = new G4Element(name="Iodine" ,symbol="I" , z= 53., a);

     a = 204.38*g/mole;
     G4Element* Tl = new G4Element(name="Thalium" ,symbol="Tl" , z= 81., a);

     a = 26.982*g/mole;
     G4Element* elAl  = new G4Element(name="element_Aluminum",symbol="elAl" , z= 13., a);

     a = 14.00*g/mole;
     G4Element* N  = new G4Element(name="Nitrogen",symbol="N" , z= 7., a);

     a = 16.00*g/mole;
     G4Element* O  = new G4Element(name="Oxygen",symbol="O" , z= 8., a);

     a = 39.95*g/mole;
     G4Element* Ar  = new G4Element(name="Argon",symbol="Ar" , z= 18., a);

     a = 51.996*g/mole;
     G4Element* Cr  = new G4Element(name="Chromium"  ,symbol="Cr" , z= 24., a);

     a = 58.69*g/mole;
     G4Element* Ni  = new G4Element(name="Nickel" ,symbol="Ni" , z= 28., a);

     a = 55.847*g/mole;
     G4Element* Fe  = new G4Element(name="Iron"  ,symbol="Fe" , z= 26., a);

     a = 12.011*g/mole;
     G4Element* C  = new G4Element(name="Carbon"  ,symbol="C" , z= 6., a);

     a = 18.998*g/mole;
     G4Element* F  = new G4Element(name="Fluorine"  ,symbol="F" , z= 9., a);

     a = 1.008*g/mole;
     G4Element* H  = new G4Element(name="Hydrogen"  ,symbol="H" , z= 1., a);


  // define Materials

   //..........Stainless Steel..........
     density = 8.0*g/cm3;
     Cr20Ni8Fe76 = new G4Material(name="Stainless_Steel", density, ncomponents=3);
     Cr20Ni8Fe76->AddElement(Cr, natoms=20);
     Cr20Ni8Fe76->AddElement(Fe, natoms=76);
     Cr20Ni8Fe76->AddElement(Ni, natoms=8);

   //..........Polytetrafluorine (PTFE)............
     density = 2.20*g/cm3;
     C2F4 = new G4Material(name="PTFE", density, ncomponents=2);
     C2F4->AddElement(C, natoms=2);
     C2F4->AddElement(F, natoms=4); 

   //..........NaI......................
     density = 3.67*g/cm3;
     NaI = new G4Material(name="Sodium Iodine", density, ncomponents=3);
     NaI->AddElement(Na, natoms=1000);
     NaI->AddElement(I, natoms=1000);
     NaI->AddElement(Tl, natoms=1);

   //..........Al.......................	
     density = 2.698*g/cm3;
     Al = new G4Material (name="Aluminum", density, ncomponents=1);
     Al->AddElement(elAl, natoms=1);
	
	
   //..........Air.....................
     density = 1.2927*mg/cm3;
     N78O21Ar1 = new G4Material (name="Air", density, ncomponents=3);
     N78O21Ar1->AddElement(N, natoms=78);
     N78O21Ar1->AddElement(O, natoms=21);
     N78O21Ar1->AddElement(Ar, natoms=1);

   //..........Acrylic.....................
     density = 1.18*g/cm3;
     C5O2H8 = new G4Material (name="Acrylic", density, ncomponents=3);
     C5O2H8->AddElement(C, natoms=5);
     C5O2H8->AddElement(O, natoms=2);
     C5O2H8->AddElement(H, natoms=8);


  // Print out Elements and Materials
    G4cout << "\n\n ####-------------------------------------------------------#### \n";
    G4cout << "\n\n\n\n\t\t #### List of elements used #### \n";
    G4cout << *(G4Element::GetElementTable());
    G4cout << "\n\n\n\n\t\t #### List of materials used #### \n";
    G4cout << *(G4Material::GetMaterialTable());
    G4cout << "\n\n ####-------------------------------------------------------#### \n";
}


G4VPhysicalVolume* DetectorConstruction::ConstructDetector()
{

// EXPERIMENTAL ROOM
  G4Tubs* room_tube = new G4Tubs("room", 0.0*cm, 100.0*cm, 300.0*cm, 0.0*deg, 360.0*deg);
  G4LogicalVolume* room_log = new G4LogicalVolume(room_tube,N78O21Ar1,"room",0,0,0);
  G4VPhysicalVolume* room_phys = new G4PVPlacement(0,G4ThreeVector(0.0*cm,0.0*cm,0.0*cm),"room",room_log,NULL,false,0);

// BEAM PIPE
  G4double outerR_beam = 19.0*mm;                   //edit this to change the radius of the beam pipe
  G4double innerR_beam = outerR_beam - 1.5*mm;      //edit this to change the thickness of the beam pipe
  G4double halflength_beam = 720.0*mm;              //edit this to change the length of the beam pipe
  G4double startAngle_beam = 0.*deg;
  G4double spanAngle_beam = 360.*deg;

  G4Tubs* beam_tube = new G4Tubs("beam_tube",innerR_beam, outerR_beam, halflength_beam, startAngle_beam, spanAngle_beam);

  G4LogicalVolume* beam_log = new G4LogicalVolume(beam_tube,Cr20Ni8Fe76,"beam_log",0,0,0);

  G4VPhysicalVolume* beam_phys = new G4PVPlacement(0,G4ThreeVector(0.0*mm,0.0*mm,100.0*mm),beam_log,"beam_phys",room_log,false,0);


// DIMENSIONS OF SuN                           **(changing these will scale the whole simulation)**
  G4double innerR_scint = 22.5*mm;               // 45mm borehole
  G4double outerR_scint = 203.0*mm;              // total of 406mm in diameter
  G4double length_scint = 101.5*mm;              // total of 406mm in length
  G4double width_Refl = 0.25*mm;                 // width of reflector 
  G4double width_Al_vert = 0.50*mm;              // width of alumiunum between each segment
  G4double width_Al_horiz = 0.75*mm;             // width of aluminum between top and bottom half
  G4double innerR_Al = 21.5*mm;                  // 43mm in center           
  G4double outerR_Al = 222.5*mm;                 // thick outer casing     


// NaI SCINTILLATOR
  G4double halflength_scint = 0.5*length_scint;
  G4double startAngle_scint = 0.0*deg;
  G4double spanAngle_scint = 180.0*deg;

  G4Tubs* scint_tube = new G4Tubs("scint_tube",innerR_scint,outerR_scint,halflength_scint,startAngle_scint,spanAngle_scint);
 
  G4LogicalVolume* scint_log = new G4LogicalVolume(scint_tube,NaI,"scint_log",0,0,0);

// REFLECTOR
  G4double innerR_Refl = innerR_scint - width_Refl;
  G4double outerR_Refl = outerR_scint + 2.0*width_Refl;
  G4double length_Refl = length_scint + 2.0*width_Refl;
  G4double halflength_Refl = 0.5*length_Refl;

  G4Tubs* refl_tube = new G4Tubs("refl_tube",innerR_Refl,outerR_Refl,halflength_Refl,startAngle_scint,spanAngle_scint);

  G4SubtractionSolid* refl_sub = new G4SubtractionSolid("refl_sub",refl_tube,scint_tube,0,G4ThreeVector(0.0*mm,width_Refl,0.0*mm));

  G4LogicalVolume*  refl_log = new G4LogicalVolume(refl_sub,C2F4,"refl_log",0,0,0);

// ALUMINUM          
  G4double length_Al = length_Refl + width_Al_vert;   
  G4double halflength_Al = 0.5*length_Al;

  G4Tubs* al_tube = new G4Tubs("al_tube",innerR_Al,outerR_Al,halflength_Al,startAngle_scint,spanAngle_scint);

  G4SubtractionSolid* al_sub = new G4SubtractionSolid("al_sub",al_tube,refl_tube,0,G4ThreeVector(0.0*mm,width_Al_horiz,0.0*mm));
 
  G4LogicalVolume*  al_log = new G4LogicalVolume(al_sub,Al,"al_log",0,0,0);


  G4double length_Al_side = 13.0*mm;   
  G4double halflength_Al_side = 0.5*length_Al_side;

  G4Tubs* al_tube_side = new G4Tubs("al_tube_side",innerR_Al,outerR_Al,halflength_Al_side,0.0*deg,360.0*deg);

  G4LogicalVolume*  al_log_side = new G4LogicalVolume(al_tube_side,Al,"al_log_side",0,0,0);


// ====================== Placing the volumes ==============================//

 // Rotation Matrix
    G4RotationMatrix* rot_180 = new G4RotationMatrix();
      rot_180->rotateZ(180*deg);

  G4double Pos_x = 0.0*mm;
  G4double Pos_y_Al = 0.0*mm;
  G4double Pos_y_Refl = width_Al_horiz;
  G4double Pos_y_Scint = Pos_y_Refl + width_Refl;
  G4double Pos_z = -1.5*width_Al_vert - 3.0*width_Refl - 3.0*halflength_scint;
  
  G4String topName;
  G4String botName;

for (int i=1; i<=4; i++)
 {

     if(i==1)
      {
        topName = "T1";
        botName = "B1";
      }
     if(i==2)
      {
        topName = "T2";
        botName = "B2";
      }
     if(i==3)
      {
        topName = "T3";
        botName = "B3";
      }
     if(i==4)
      {
        topName = "T4";
        botName = "B4";
      }

  // TOP OF SUN

     Pos_y_Al = 0.0*mm;
     Pos_y_Refl = width_Al_horiz;
     Pos_y_Scint = Pos_y_Refl + width_Refl;

     //aluminum
     G4VPhysicalVolume* al_top = new G4PVPlacement(0,G4ThreeVector(Pos_x,Pos_y_Al,Pos_z),al_log,"al_top",room_log,false,0);

     //reflector  
     G4VPhysicalVolume* refl_top = new G4PVPlacement(0,G4ThreeVector(Pos_x,Pos_y_Refl,Pos_z),refl_log,"refl_top",room_log,false,0);

     //scintillator
     G4VPhysicalVolume* scint_top = new G4PVPlacement(0,G4ThreeVector(Pos_x,Pos_y_Scint,Pos_z),scint_log,topName,room_log,false,0);


  // BOTTOM OF SUN

     Pos_y_Al = 0.0*mm;
     Pos_y_Refl = -width_Al_horiz;
     Pos_y_Scint = Pos_y_Refl - width_Refl;

     //aluminum
     G4VPhysicalVolume* al_bottom = new G4PVPlacement(rot_180,G4ThreeVector(Pos_x,Pos_y_Al,Pos_z),al_log,"al_bottom",room_log,false,0);

     //reflector  
     G4VPhysicalVolume* refl_bottom = new G4PVPlacement(rot_180,G4ThreeVector(Pos_x,Pos_y_Refl,Pos_z),refl_log,"refl_bottom",room_log,false,0);

     //scintillator
     G4VPhysicalVolume* scint_bottom = new G4PVPlacement(rot_180,G4ThreeVector(Pos_x,Pos_y_Scint,Pos_z),scint_log,botName,room_log,false,0);


     Pos_z = Pos_z + width_Al_vert + 2.0*width_Refl + length_scint;
   }


// SIDES OF SUN

  Pos_x = 0.0*mm;
  Pos_y_Al = 0.0*mm;
  Pos_z = 2.0*length_scint + 2.0*width_Al_vert + 4.0*width_Refl + halflength_Al_side; 
  G4VPhysicalVolume* al_sideA = new G4PVPlacement(0,G4ThreeVector(Pos_x,Pos_y_Al,Pos_z),al_log_side,"al_sideA",room_log,false,0);
  G4VPhysicalVolume* al_sideB = new G4PVPlacement(0,G4ThreeVector(Pos_x,Pos_y_Al,-Pos_z),al_log_side,"al_sideB",room_log,false,0);

 
// **************************************************************************************************
//  FOR THE CODE TO PROPERLY SAVE THINGS TO ROOT, YOU NEED TO TELL IT WHAT YOU NAMED YOUR DETECTORS
// **************************************************************************************************
//              The name of the detectors is in the G4VPhysicalVolume command                      
	  detectorName[0] = "T1";
	  detectorName[1] = "T2";
	  detectorName[2] = "T3";
	  detectorName[3] = "T4";
	  detectorName[4] = "B1";
	  detectorName[5] = "B2";
	  detectorName[6] = "B3";
	  detectorName[7] = "B4";

// **************************************************************************************************



//____________THE TARGET HOLDER______________________

  G4double innerR_pipe = 3.64*0.5*mm;	 //tubes for air cooling   
  G4double outerR_pipe = 4.76*0.5*mm;               
  G4double halflength_pipe =879.39*0.5*mm;  

  G4double innerR_holder = 0.0*mm;	//holder  
  G4double outerR_holder = 17.15*mm;               
  G4double halflength_holder =4.76*0.5*mm;  

  G4double halfX_top = 11.52*mm;	//remove top part of holder
  G4double halfY_top = 5.0*mm;
  G4double halfZ_top = halflength_holder+1.0*mm;

  G4double halfX_indent = 17.17*0.5*mm;	//indent for target frame
  G4double halfY_indent = 20.73*0.5*mm;
  G4double halfZ_indent = 4.16*0.5*mm;

  G4double halfX_hole = 13.11*0.5*mm;	//hole for beam
  G4double halfY_hole = 16.77*0.5*mm;
  G4double halfZ_hole = halflength_holder+1.0*mm;

  G4double cutout_halfX1=13.465*mm;	//remove material 
  G4double cutout_halfX2=13.185*mm;
  G4double cutout_halfY1=2.38*0.5*mm;
  G4double cutout_halfY2=2.38*0.5*mm;
  G4double cutout_halfZ =2.54*0.5*mm;

  G4double innerR_cutout = 0.0*mm; 	//remove more material
  G4double outerR_cutout = 6.06*mm;               
  G4double halflength_cutout =2.54*0.5*mm;   

  G4double innerR_end = 0.0*mm;		//end where you hold it
  G4double outerR_end = 54.86*0.5*mm;               
  G4double halflength_end =3.05*0.5*mm;     

  G4double innerR1_endcap = 0.0*mm;	//endcap where you hold it
  G4double outerR1_endcap = 54.86*0.5*mm;   
  G4double innerR2_endcap = 0.0*mm;
  G4double outerR2_endcap = 39.70*0.5*mm;              
  G4double halflength_endcap = 2.03*0.5*mm;    

  G4double innerR_endHole1 = 0.0*mm;	//hole for air cooling
  G4double outerR_endHole1 = 3.64*0.5*mm;               
  G4double halflength_endHole1 =halflength_end+1.0*mm;   

  G4double innerR1_endHole2 = 0.0*mm;	//hole for air cooling
  G4double outerR1_endHole2 = 4.85*0.5*mm;   
  G4double innerR2_endHole2 = 0.0*mm;
  G4double outerR2_endHole2 = 6.38*0.5*mm;              
  G4double halflength_endHole2 =halflength_endcap+1.0*mm;      
          
  G4Tubs* pipe_tube = new G4Tubs("pipe_tube",innerR_pipe, outerR_pipe, halflength_pipe, 0.0*deg, 360.0*deg);
  G4Tubs* holder_tube = new G4Tubs("holder_tube",innerR_holder, outerR_holder, halflength_holder, 0.0*deg, 360.0*deg);
  G4Box* top_box = new G4Box("top_box",halfX_top,halfY_top,halfZ_top);
  G4Box* indent_box = new G4Box("indent_box",halfX_indent,halfY_indent,halfZ_indent);
  G4Box* hole_box = new G4Box("hole_box",halfX_hole,halfY_hole,halfZ_hole);
  G4Trd* cutout = new G4Trd("cutout",cutout_halfX1,cutout_halfX2,cutout_halfY1,cutout_halfY2,cutout_halfZ);
  G4Tubs* cutout_tube1 = new G4Tubs("cutout_tube",innerR_cutout, outerR_cutout, halflength_cutout, 90.0*deg, 90.0*deg);
  G4Tubs* cutout_tube2 = new G4Tubs("cutout_tube",innerR_cutout, outerR_cutout, halflength_cutout, 0.0*deg, 90.0*deg);
  G4Tubs* end_tube = new G4Tubs("end_tube",innerR_end, outerR_end, halflength_end, 0.0*deg, 360.0*deg);     
  G4Cons* endcap_cone = new G4Cons("endcap_cone",innerR1_endcap, outerR1_endcap, innerR2_endcap, outerR2_endcap, halflength_end, 0.0*deg, 360.0*deg);        
  G4Tubs* endHole_tube = new G4Tubs("endHole_tube",innerR_endHole1, outerR_endHole1, halflength_endHole1, 0.0*deg, 360.0*deg);    
  G4Cons* endHole_cone = new G4Cons("endHole_cone",innerR1_endHole2, outerR1_endHole2, innerR2_endHole2, outerR2_endHole2, halflength_endHole2, 0.0*deg, 360.0*deg);
 
  G4SubtractionSolid* holder_sub1 = new G4SubtractionSolid("holder_sub1",holder_tube,top_box,0,G4ThreeVector(0.0*mm,12.705*mm+halfY_top,0.0*mm));
  G4SubtractionSolid* holder_sub2 = new G4SubtractionSolid("holder_sub2",holder_sub1,indent_box,0,G4ThreeVector(0.0*mm,0.0*mm,halfZ_indent));
  G4SubtractionSolid* holder_sub3 = new G4SubtractionSolid("holder_sub3",holder_sub2,hole_box,0,G4ThreeVector(0.0*mm,0.0*mm,0.0*mm));           
  G4SubtractionSolid* holder_sub4 = new G4SubtractionSolid("holder_sub4",holder_sub3,cutout,0,G4ThreeVector(0.0*mm,4.705*mm,halflength_holder));    
  G4SubtractionSolid* holder_sub5 = new G4SubtractionSolid("holder_sub5",holder_sub4,cutout_tube1,rot_180,G4ThreeVector(7.035*mm,-3.425*mm,halflength_holder));
  G4SubtractionSolid* holder_sub6 = new G4SubtractionSolid("holder_sub6",holder_sub5,cutout_tube2,rot_180,G4ThreeVector(-7.035*mm,-3.425*mm,halflength_holder));

  G4SubtractionSolid* end_sub1 = new G4SubtractionSolid("end_sub1",end_tube,endHole_tube,0,G4ThreeVector(12.19*mm,0.0*mm,0.0*mm));
  G4SubtractionSolid* end_sub2 = new G4SubtractionSolid("end_sub2",end_sub1,endHole_tube,0,G4ThreeVector(-12.19*mm,0.0*mm,0.0*mm));

  G4SubtractionSolid* endcap_sub1 = new G4SubtractionSolid("endcap_sub1",endcap_cone,endHole_cone,0,G4ThreeVector(12.19*mm,0.0*mm,0.0*mm));
  G4SubtractionSolid* endcap_sub2 = new G4SubtractionSolid("endcap_sub2",endcap_sub1,endHole_cone,0,G4ThreeVector(-12.19*mm,0.0*mm,0.0*mm));

  G4LogicalVolume* pipe_log = new G4LogicalVolume(pipe_tube,Al,"pipe_log",0,0,0);
  G4LogicalVolume* holder_log = new G4LogicalVolume(holder_sub6,Al,"holder_log",0,0,0);
  G4LogicalVolume* end_log = new G4LogicalVolume(end_sub2,Al,"end_log",0,0,0);
  G4LogicalVolume* endcap_log = new G4LogicalVolume(endcap_sub2,Al,"endcap_log",0,0,0);

  G4VPhysicalVolume* holder_phys = new G4PVPlacement(0,G4ThreeVector(0.0*mm,0.0*mm,0.0*mm),holder_log,"holder_phys",room_log,false,0);

  G4VPhysicalVolume* pipe1_phys = new G4PVPlacement(0,G4ThreeVector(12.19*mm,0.0*mm,halflength_holder+halflength_pipe),pipe_log,"pipe1_phys",room_log,false,0);

  G4VPhysicalVolume* pipe2_phys = new G4PVPlacement(0,G4ThreeVector(-12.19*mm,0.0*mm,halflength_holder+halflength_pipe),pipe_log,"pipe2_phys",room_log,false,0);
 
  G4VPhysicalVolume* end_phys = new G4PVPlacement(0,G4ThreeVector(0.0*mm,0.0*mm,halflength_holder+2.0*halflength_pipe+halflength_end),end_log,"end_phys",room_log,false,0);

  G4VPhysicalVolume* endcap_phys = new G4PVPlacement(0,G4ThreeVector(0.0*mm,0.0*mm,halflength_holder+2.0*halflength_pipe+2.0*halflength_end+halflength_endcap),endcap_log,"endcap_phys",room_log,false,0);




// VISUALIZATION STUFF

  room_log->SetVisAttributes (G4VisAttributes::Invisible);

//visualization for scintillators = GREEN
  G4VisAttributes *GreenAttr = new G4VisAttributes(G4Colour(0.,1.,0.));     
  GreenAttr->SetVisibility(true);
  GreenAttr->SetForceSolid(true);

//visualization for reflector = PURPLE
  G4VisAttributes *PurpleAttr = new G4VisAttributes(G4Colour(1.,0.,1.));  
  PurpleAttr->SetVisibility(true);
  PurpleAttr->SetForceSolid(true);

//visualization for aluminum = GREY
  G4VisAttributes *GreyAttr = new G4VisAttributes(G4Colour(0.5,0.5,0.5));
  GreyAttr->SetVisibility(true);
  GreyAttr->SetForceSolid(true);

//visualization for BLUE
  G4VisAttributes *BlueAttr = new G4VisAttributes(G4Colour(0.,0.,1.));
  BlueAttr->SetVisibility(true);
  BlueAttr->SetForceSolid(true);

//visualization for RED
  G4VisAttributes *RedAttr = new G4VisAttributes(G4Colour(1.,0.,0.));
  RedAttr->SetVisibility(true);
  RedAttr->SetForceSolid(true);

// applying the color scheme
  //scint_log->SetVisAttributes(GreenAttr);
  //refl_log->SetVisAttributes(PurpleAttr);
  //al_log->SetVisAttributes(GreyAttr);
  //al_log_side->SetVisAttributes(GreyAttr);
  //beam_log->SetVisAttributes(BlueAttr);
  holder_log->SetVisAttributes(GreyAttr);
  pipe_log->SetVisAttributes(GreyAttr);
  end_log->SetVisAttributes(GreyAttr);
  endcap_log->SetVisAttributes(GreyAttr);
  return room_phys;

}

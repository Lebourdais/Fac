/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Feb 12 11:18:58 CET 2018
*
*/

import java.awt.Color;

import java.awt.GradientPaint;

import java.awt.Graphics;

import java.awt.Graphics2D;

import java.awt.Image;

import java.awt.event.MouseEvent;

import java.awt.event.MouseListener;

import java.io.File;

import java.io.IOException; 

import javax.imageio.ImageIO;

import javax.swing.JButton;

  

public class Bouton extends JButton implements MouseListener{

  private String name;
  private GradientPaint gp;

  public Bouton(String str){

    super(str);
	this.gp = new GradientPaint(0, 0, Color.blue, 0, 20, Color.green, true);
    this.name = str;
	this.addMouseListener(this);
  }

        

  public void paintComponent(Graphics g){

    Graphics2D g2d = (Graphics2D)g;

    //GradientPaint gp = new GradientPaint(0, 0, Color.blue, 0, 20, Color.red, true);

    g2d.setPaint(this.gp);

    g2d.fillRect(0, 0, this.getWidth(), this.getHeight());

    g2d.setColor(Color.white);

    g2d.drawString(this.name, this.getWidth() / 2 - (this.getWidth()/ 2 /4), (this.getHeight() / 2) + 5);

  }   

  //Méthode appelée lors du clic de souris

  public void mouseClicked(MouseEvent event) { }


  //Méthode appelée lors du survol de la souris

  public void mouseEntered(MouseEvent event) { 
  	this.gp = new GradientPaint(0, 0, Color.green, 0, 20, Color.yellow, true);	
  	
  }


  //Méthode appelée lorsque la souris sort de la zone du bouton

  public void mouseExited(MouseEvent event) {
  	this.gp = new GradientPaint(0, 0, Color.blue, 0, 20, Color.green, true);
  }


  //Méthode appelée lorsque l'on presse le bouton gauche de la souris

  public void mousePressed(MouseEvent event) {
  	this.gp = new GradientPaint(0, 0, Color.red, 0, 20, Color.orange, true);	
  }


  //Méthode appelée lorsque l'on relâche le clic de souris

  public void mouseReleased(MouseEvent event) {
  	this.gp = new GradientPaint(0, 0, Color.blue, 0, 20, Color.green, true);	
  }      

}
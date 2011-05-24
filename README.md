PiewPiew Drupal Utilities
-------------------------
The PiewPiew Drupal utilities are a collection of Drush commands and shell
scripts designed to streamline the process of setting up and maintaining a
Drupal development project. In a nutshell, these utils simply make it super
easy to adopt a number of "best practice" tools and techniques in order to 
support a smooth Drupal development workflow, from the initial creation of a
project, through to version controlling your project, and finally to 
deployment.

The PiewPiew utilities take a lot of the leg-work out of setting up and 
maintaining a custom Drupal install profile, as well as related Drush Make
and SVN configuration. 

Install profiles offer a means to easily package up al the depencies required to deploy a Drupal site, including custom and contributed modules, themes and configurations. 

The  combination of Install Profiles and Drush Make is widely acknowledged 
as a "best practice" approach to Drupal development, and is the foundation 
upon which the packaging systems used to distribute projects on drupal.org is
built.

Requirements
------------
In order to make the most of these utils, you'll need to have the very
excellent Drush (http://drupal.org/project/drush) up and running, as well as 
the Drush Make command (http://drupal.org/project/drush_make). It is highly
recommended that you also have the svn cli executable installed, in order to
make full use of the svn utilities.

Installing
----------
Copy the folder containing this README.md file to a location that can be 
located by the drush executable. Your best bet is to place it in ~/.drush 
(note you may need to create this folder yourself)

Usage
-----

To commence development, we first run the 'create-project' drush command. In
its most simple form - 

  drush create-project myproject

This will create a new project in a folder named 'myproject'. In the folder
you'll find a 'build.make' file, and a 'profile' folder.

The profile folder contains a skeleton Drupal install profile. During the 
development process you will flesh out this profile by:

- defining contrib modules and themes required by your site in myproject.make
- implementing a custom install profile in myproject.profile
- developing custom modules and themes in the /modules/custom and 
  /themes/custom folders.



Drush command wishlist
----------------------

Create a new project. This command should

- Create a build.make file, containing downloads for drupal core, this drupal 
  dev utility module and the custom install profile for the project. Probably 
  a good idea for this build.make file to contain a lot of examples and 
  comments
  
- Set up an empty installation profile folder, complete with it's own 
  profile.make and profilename.profile php file.
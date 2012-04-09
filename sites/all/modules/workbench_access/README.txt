/**
 * @file
 * README file for Workbench Access.
 */

Workbench Access
A pluggable, hierarachical editorial access control system

CONTENTS
--------

1.  Introduction
1.1   Use-case
1.2   Examples
1.2.1  Extending a section
1.2.2  Ignoring sections
1.3   Terminology
1.4   Managing editorial sections
1.5   Access control notes
2.  Installation
2.1   Dependencies
3.  Permissions
4.  Configuration
4.1   Access schemes
4.1.1 Content types enabled
4.1.2  Automated section assignment
4.1.3  Workbench Access message label
4.1.4  Allow multiple section assignments
4.2   Access sections
4.2.1  Manual section configuration
4.2.2  Automated section configuration
4.2.3 Editing sections in native forms
4.3   Assigning editors to sections
4.4   Assigning roles to sections
5.  Using the module
5.1   Assigning nodes to sections
5.2   Viewing assigned content
5.3   Viewing assigned sections
5.4   Batch updating content
6.  Troubleshooting
7.  Developer notes
7.1   API documentation
7.2   Database schema
7.3   Views integration
8.  Feature roadmap


----
1.  Introduction

Workbench Access creates editorial access controls based on hierarchies. It is
an extensible system that supports structures created by other Drupal modules.

When creating and editing content, users will be asked to place the content in
an editorial section. Other users within that section or its parents will be
able to edit the content.

A user may be granted editorial rights to a section specific to his account or
by his assigned role on the site.

As of this writing, the module supports Taxonomy and Menu modules for the
management of access hierarchies.

Note that the module only controls access to content editing. It does not
provide any content filtering of access restrictions for users trying to view
that content.

While Workbench Access is part of a larger module suite, it may be run as a
stand-alone module with no dependencies.

For more information about Workbench, see http://drupal.org/project/workbench.

----
1.1  Use-case

The above description is abstract, so let's look at a practical use-case.

Imagine that you work for a large university. The university is divided as
follows:

  -- The University
    -- Colleges
      -- College of Arts and Sciences
        -- Art
        -- Biology
        -- Physics
      -- School of Medicine
        -- Dentistry
        -- Medicine
        -- Nursing
    -- Staff
      -- Administration
      -- Faculty
      -- Support Staff
    -- Students
      -- Prospective Students
      -- Current Students
      -- Alumni
      
In such a system, people who are part of the Biology department have no
authority inside the Nursing group. The two groups are separate parts of the
hierarchy. The chair of the Biology department, therefore, cannot set policy for
the Nursing school.

Biology and Art, however, are both sub-groups of the College of Arts and
Sciences. While the chair of Biology cannot set policy for the Art department,
the Dean of the College of Arts and Sciences can set policy for both
departments.

For websites, this concept of authority often affects who can create and edit
content within different areas of a large site. Workbench Access provides a
flexible tool for defining and managing these rules.


----
1.2  Examples

In the above scenario, The University is the root element of the hierarchy. All
other elements are "children" of this "parent" item. Individual items can
themselves have children.

For our University, the following relationship exists:

  - Alumni is a child of Students
  - Students are a child of The University

When we grant access rights for content editors, we can therefore decide if a
user should be able to edit any of the following:

  -- All content in The University and all its children
  -- All content in Students and all its children
  -- Only content in Alumni

In practice, this means that the Dean can have wide authority over that part of
the website that she is responsible for, while a student intern might have very
limited roles.

In our University, we have three types of web site users:

  - Editors are responsible for the entire site.
  - Deans are responsible for an entire College.
  - Writers are responsible for specific departments.

In this scenario, Workbench Access would be configured as follows:

  -- Jane Doe, site editor
    -- Assigned to The University section.
    -- Can edit content on the entire site.

  -- John Smith, Dean of Medicine
    -- Assigned to the School of Medicine section.
      -- Can edit content in the following sections:
        -- School of Medicine
          -- Dentistry
          -- Medicine
          -- Nursing

  -- Ken Johnson, Alumni relations director
    -- Assigned to the Alumni section.
      -- Can edit content in the Alumni section.
      
  -- Paula Thompson, Dental school administrator
    -- Assigned to the Dentistry section.
      -- Can edit content in the Dentistry section.
      
What makes this system powerful is the inheritance of permissions based on the
organizational hierarchy.  Put another way, you will see that:

  -- Jane Doe
    -- Can edit all content, including that posted by:
      -- John Smith
      -- Ken Johnson
      -- Paula Thompson
      
  -- John Smith
    -- Can edit School of Medicine content, including that posted by:
      -- Paula Thompson
      
  -- Ken Johnson, Alumni relations director
    -- Can edit content in the Alumni section.
      
  -- Paula Thompson, Dental school administrator
    -- Can edit content in the Dentistry section.


----
1.2.1 Extending a section

Let's say that Paula Thompson hires two writers for the Dental school. Those
writers can be assigned to the Denistry section as well, so that Paula can edit
their content.  We can even use Drupal's tools to extend the Dentistry section
as follows:

  -- Dentistry
    -- Courses
    -- Faculty
    -- Policies
      -- Regulatory compliance
      -- University regulations
      
Suppose, then, that one of our new hires is Pete Peterson, an expert in
regulatory compliance. Pete can be assigned to work on just that section of the
site.


----
1.2.2  Ignoring sections

By default, all elements of a hierarchy are set as editorial sections. But it
may be that your organization does not need the full complexity. Perhaps your
hierarchy can stop at the Students level.

For this case, Workbench Access allows you to disable select terms within the
hierarchy, so that not all options need to be considered when assigning
editorial access.

A simplified editorial structure for our University might look like so:

  -- The University
    -- Colleges
      -- College of Arts and Sciences
        -- Art
        -- Biology
        -- Physics
      -- School of Medicine
    -- Staff
    -- Students
      -- Alumni

In this case, the 'Prospective Students' section would simply fall under the
'Students' area. We retain Alumni as a special case, since that section has
distinct editorial needs.

This 'partial hierarchy' system is very useful when you use the hierarchy for
one purpose -- like site navigation or information architecture -- but don't
need the same complexity for editorial access.

But don't panic. You don't have to use this feature if you don't need it.

See section 4.1.1 Automated section assignment for information about enabling
this option.


----
1.3   Terminology

Throughout this documentation and when using the module, you will run across
terms that have special meaning. This brief glossary tries to explain those
terms.

  -- user
      A site visitor who may have specific editorial privileges. If the user has
      these editorial privileges, she is referred to as an editor.

  -- user roles
      Drupal's method for grouping permissions assigned to an entire class of
      users.

  -- section
      One or more definitions that can be used to tag content for use by
      specific editorial groups. A section defines the editorial assignments
      that can be given to individual users or to entire user roles.

  -- access scheme
      A rule set used to define and control section definitions. A taxonomy
      access scheme, for instance, uses sections defined by the core Taxonomy
      module.

  -- editors
      Individual members assigned to an editorial section.
      
  -- roles
      User roles assigned to an editorial section.

If you find part of the user interface violating these definitions, please file
a bug report at http://drupal.org/project/workbench_access.


----
1.4  Managing editorial sections

Creating and assigning editorial access is a three-stage process. Simply put:

  1) Define the access scheme your site will use.

  2) Designate the active editorial sections you site will use.
  
  3) Assign editors to the appropriate sections.

We will discuss this process in more detail throughout this document.

The section structure itself is always controlled by another module -- as we
mentioned, both Taxonomy and Menu modules are supported. Since Drupal already
has tools for managing hierarchies, it would be wasteful to create another.
Instead, we try to use existing site concepts and workflow to enhance your
editorial options.


----
1.5   Access control notes

For those of you familiar with Drupal, we should point out that Workbench Access
is not a Node Access module. That is, it will not restrict what content users
can view on the site.

Instead, Workbench Access targets the content creators and administrators,
giving them a tool for organizing editorial responsibilities.

If you need to restrict the ability to view content, you may wish to consider
another module, such as Organic Groups (http://drupal.org/project/og) or
Domain Access (http://drupal.org/project/domain).

You could also write an extension module that handles this for Workbench. If
that interests you, see the Developer Notes section of this document.


----
2.  Installation

Install the module and enable it according to Drupal standards.

After enabling the module, you wil be asked to configure its settings.
On the configuration screen, you may choose to install a test
vocabulary. This vocabulary will help you learn how Workbench Access
works.

When you install the test vocabulary, it will create a test access scheme for
you. This scheme is called 'Museum' and it is created as a Taxonomy vocabulary.
(It has a machine name of 'workbench_access', however.)

You should be able to view the structure at the path:

    Admin > Structure > Taxonomy > Museum

You may use this to build your access hierarchy if you wish.  Simply edit the
term names to reflect the real use-case for your site.

The created hierarchy mimics a Museum web site, divided into three sections,
each of which has child sections for Staff and Visitor pages:

  -- Museum
    -- Exhibits
      -- Staff
      -- Visitors
    -- Library
      -- Staff
      -- Visitors
    -- Gift Shop
      -- Staff
      -- Visitors

All existing site content will be assigned to the top-level section.

By default, user 1 (the administrative super-user) is assigned to the top-level
section, giving this account access to edit all content.

Note that when you install the module, users who are not assigned to an
editorial section may no longer be able to create or edit content. This is
normal. Since Workbench Access now controls who can create and edit content, you
will need to configure the module before resuming normal site operations.

Workbench Access rules will not be enforced until an active editorial section is
created.

----
2.1   Dependencies

Workbench Access requires the core Taxonomy module to be active on your site.

----
3.  Permissions

Workbench Access comes with four permissions.

  -- Administer Workbench Access settings
  Allows users to configure Workbench Access access schemes and sections.

  -- Assign users to Workbench Access sections
  Allows users to assign editors to sections. (Note that these editors must have
  the 'Allow all members of this role to be assigned to Workbench sections'
  permission described below.

  -- Allow all members of this role to be assigned to Workbench Access sections
  Allows a user to be assigned as an editor of a section. This permission is
  used to check whether a user can access Workbench Access forms and features.
  Users without this permission will not be allowed to create, edit or delete
  content.

  -- Batch update section assignments for content
  Allows a user to access the batch update form at admin/content. See section
  5.4 for details.

  -- View Workbench Access information 
  Allows users to see information and messages related to Workbench Access,
  particularly section assignments of content pages. Useful for debugging and
  support.

  -- View taxonomy term pages for Workbench Access vocabulary
  Workbench Access can create its own vocabulary for data storage. Typically,
  this vocabulary should not be shown to site visitors. This permission
  restricts access to taxonomy pages (taxonomy/term/%) defined by Workbench
  Access. Normal access to custom vocabularies is not affected. Only give this
  permission to roles that need to view these term pages, effectively treating
  them as standard taxonomy terms.

As a general rule, none of these permissions should ever be given to the
anonymous user role.

Note that having the permission to become an editor does not automatically make
a user an editor. Once the user has the permission, she must be assigned to
sections in order to edit content.  See the next section for details.

----
4.  Configuration

There are three steps to proper module configuration. After setting up proper
permissions, you should proceed through the steps below.

----
4.1   Access schemes

As discussed in the Installation section, Workbench Access auto-installs a test
configuration for you. This process is designed to help you understand how the
module functions.

When you are done testing, the next step is to decide on the active access
scheme for the site. The access scheme defines how editorial sections are
defined and managed.

The Workbench Access settings page (admin/config/workbench/access/settings)
shows the available access schemes. By default, these are Menu and Taxonomy.

The form element will look similar to:

    Active access scheme *
    ( ) Menu
    Uses the menu system for assigning hierarchical access control.
    (*) Taxonomy 
    Uses taxonomy vocabularies for assigning hierarchical access control.

You must select one option (Taxonomy is the default). Note that once your site
goes live, changing this value may disrupt your workflow.

After selecting the active scheme, you can enable the top-level sections for
that scheme. For Taxonomy-based access, these are Vocabularies. For Menu-based
access, these are Menus.

The form element will look similar to:

    Taxonomy scheme settings
    Changing this value in production may disrupt your workflow.

    Editorial vocabulary
    [*] Museum
    [ ] Tags
    Select the vocabularies to be used for access control.

You may activate multiple top-level sections. In our example documentation, The
University would be a top-level section. By default, the active top-level
section is the Museum vocabulary created during installation.

Select your options and Save configuration.

----
4.1.1 Content types enabled

This fieldset determines is access control rules will be enforced on each
content type. You may select to disable complex access rules for any content
type.

  > Content types enabled
  [*] Article
  [*] Basic page
  Only selected content types will have Workbench Access rules enforced.

By default, access control is enforced for all content types.

Note that these settings are also available under the "Workflow" tab of the
content type settings page.

----
4.1.2  Automated section assignment

On the settings page is another checkbox, labeled 'Automated section
assignment'. This optional setting is enabled by default.

    [*] Automated section assignment
    Enable all sections automatically for the active scheme.

This convenient setting automatically declares that all elements of the selected
access scheme are active editorial sections. if you need the advanced
configuration options described in 1.2.2  Ignoring sections, then you should
uncheck this box.

If you leave this box checked, you can skip section 4.2, since your sections are
automatically configured for you.


----
4.1.3  Workbench Access message label

In the user interface, Workbench Access sets certain messages, such as the
assigned editorial sections and the form label.

This settings lets you change how the item is labelled. The default is
"Workbench Access". You may prefer "Sections" or "Editorial Team" instead.

----
4.1.4  Allow multiple section assignments

The checkbox labeled 'Allow multiple section assignments' controls the behavior
of the section selection form when editing content. This optional setting is
disabled by default.

    [ ] Allow multiple section assignments
    Let content be assigned to multiple sections.

If enabled, editors will be shown a multiple select option when editing section
assignments. This configuration can be useful if you have content that spans
several parts of your organization.


----
4.2   Access sections

Once you have declared an access scheme, you may enable the sections for that
scheme. This process can be automated (as explained above) or manual.

Access sections are configured at the Sections tab of the settings
(admin/config/workbench/access/sections). This page shows the hierarchy of all
the active schemes on your site.

Once you have configured these options, you may assign editors to sections.


----
4.2.1  Manual section configuration

Each top-level item and its children are displayed in a separate fieldset. If a
fieldset has no active sections, it will display collapsed.

The default page looks like so:

  + Museum
    [*] All of Museum
    [*] - Exhibits
    [*] -- Exhibits Staff
    [*] -- Exhibits Visitors
    [*] - Library
    [*] -- Library Staff
    [*] -- Library Visitors
    [*] - Gift Shop
    [*] -- Gift Shop Staff
    [*] -- Gift Shop Visitors

Items are ordered by their parent->child relationship. The hierarchy of your
access scheme is represented by the -- marks in the interface. In this case, we
can see that:

    Library Visitors is a child of Library is a child of All of Museum.

Your editors may be assigned to any active section. To disable a section,
uncheck the option and save the configuration.

Note that disabling a section will remove any editors from an existing setting.
We recommend configuring this screen once for your site.

----
4.2.2  Automated section configuration

If using automated sections, as described in 4.1.1, you will see a message at
the top of the Sections page:

  All sections are set to be active automatically. Disable the Automated section
  assignment option to make changes.

If this is the case, all options will be disabled and the submit button will be
removed.

----
4.2.3 Editing sections in native forms

When using the Menu or Taxonomy schemes, you may enable or disable sections
when using the native editing forms for those modules. Only roles with the
'Administer Workbench Access settings' permission may perform this action.

At the bottom of a form, look for the checkbox:

    [ ] Workbench Access editorial section
    Enable this menu as an active editorial section.

If using Automated section configuration, these checkboxes may be selected
and disabled for you. Otherwise, select the proper status for each item as you
edit.

Note that removing a section also removes all editors and content from that
section.

----
4.3   Assigning editors to sections

The Editors tab shows you the active editorial sections for your site and the
number of users assigned to each section. The page is located at:
(admin/config/workbench/access).

This page shows all active sections, ordered according to the hierarchy.

In the secondary column is the count of the users assigned to the section as
editors. In a default installation, only one editor is assigned (user 1) to the
Museum section.

Clicking either the section title link or the editors count link will take you
to a screen that shows a list of active editors for that section.

From this screen, you may add editors by using the autocomplete text form
labeled 'Add editors'. Simply start typing the username to find a list of
matching records. Once you have selected a user, submit the 'Update editors'
button to save the changes.

You may remove an active editor by checking the 'remove' option next to a
username and submitting the form.

Users who may 'Assign users to Workbench sections' may also assign editors from
a user account page. Click on the 'Sections' tab of the user's account to see a
list of all sections. Simply check the boxes for the desired assignments.

When adding an editor, remember that permissions cascade from parent to child.
If you want an editor to access the entire Library section, you only need to
assign that user to the Library section, the child permissions are inherited
automatically.


----
4.4   Assigning roles to sections

Similar to the Editors tab, the Roles tab presents an overview of active
editorial sections and the assigned roles for those sections. The Roles tab is
located at (admin/config/workbench/access/roles).

Click either the section or role count links to enter the role assignment
screen. This screen also has two parts. The first is a table showing all users
who are in the roles assigned to the section. The user's role(s) that grant this
access are shown as well.

The second element is a set of checkboxes for each role which has the 'Allow all
members of this role to be assigned to Workbench sections' permission. This part
of the form will look similar to:

    Roles
    [ ] authenticated user
    [ ] administrator
    Select the role(s) that should have all users assigned to this section.

Simply check the roles that you wish to use for this section. This feature will
automatically assign all users of that roles to be editors of the section.

Technical note: The role settings are applied dynamically and not stored with
the user account. In effect, if you assign an editor to a section, the editor
must be manually removed from that section to remove access. However, if you
assign a role to a section, all editors in that role can be removed by disabling
the role's access.

For example, if a user named 'falstaff' is assigned as a Museum editor, and
falstaff is in the 'administrator' role, removing the administrator role from
the Museum section will remove all administrators _except for_ falstaff, since
his assignment is specific to his account.


----
5.  Using the module

Now that we have configured our access scheme and assigned editors, we can
resume normal site operations. The major feature of Workbench Access is to
assign content (or Drupal 'node') to a specific editorial section.

Note that users who are not assigned to an editorial section may not be allowed
to create content on the site.


----
5.1   Assigning nodes to sections

By design, Workbench Access provides its own editing form element. This element
is assigned to all content types on your site.

On the content editing screen, the Workbench Access element will appear as a
selection list. This form element is specific to the current editor. The
selection options will only display the sections that the user can access. For
example, our Library editor will have a form similar to:

    Workbench access *
    <select>
      - Library
      -- Library Staff
      -- Library Visitors
    </select>
    Select the proper editorial group for this content.

The editor may select the proper section using this form element. At this time,
only single-section assignments are supported.

Note that Drupal may allow the user to edit content that is not in the user's
assigned sections if another access control module intervenes. In this case, the
user will see a message indicating the current section:

    Workbench access 
    Test article is assigned to the Museum editorial group and may not be
    changed.

Most frequently, this is true if the user can 'Bypass node access' or is logged
in as user 1.


----
5.2   Viewing assigned content

When Workbench Access is installed without Workbench, , it provides a tab on the
user account page, labeled Content.  This page shows a list of all content
assigned to the user's editorial sections.

When Workbench Access and Workbench are both enabled, you can find this same
functionality in Workbench -> My Content -> All Recent Content.

This table may be sorted and searched to help editors find content quickly.

The 'Section' column of the table shows the current section the content is
assigned to. If the editor is assigned to that section, the section name is
shown.

For example, if the editor is assigned to the Library section, the table may
look like so:

    Title           Section
    -----           -------
    Library hours   Library
    Return policy   Library Visitors
    Vacation rules  Library Staff

This column is designed to show editors why they have access to the content.


----
5.3   Viewing assigned sections

Workbench Access provides a tab on the user account page, labeled Sections.
This page shows a list of all sections the user is assigned to.

If viewed by a user who may 'Assign users to Workbench Access sections', this
page will be a form that allows section assignment. Check the boxes to set the
proper sections for the user.

----
5.4   Batch updating content

Workbench Access provides an option on the Content batch review screen which
allows editors with the 'Batch update section assignments for content'
permission to set the section for content during batch updates.

If you go to admin/content, you will see an Update Options form select list.
If you are assigned to editorial sections, the form will display a 'Set
editorial section' option with a list of the sections you may assign.

Note that this is a powerful tool and will override choices made by other users.
Any content can be reassigned when using this form.


----
6.  Troubleshooting

Some helpful tips to make answering questions easier.

-- Users who are not assigned to an editorial section may not be allowed
to create content on the site.

-- Editorial access applies to _all_ content types in a given section.

-- Editorial access assigned to an individual user is not removed if that user's
role is removed from an editorial section.

-- Role-based access is added dynamically to all users in the role.

-- When viewing content as a user with the 'View Workbench Access information'
permission, a message will be displayed at the top of the page indicating the
assigned section and whether or not the user may edit the page.

-- For advanced access debugging, download the Devel module
(http://drupal.org/project/devel) and enable the Devel Node Access module and
the 'Devel Node Access by User' block. This block will output the access control
rules for recent visitors to any content.


----
7.  Developer notes

The following section documents technical details of interest to developers.


----
7.1   API documentation

Workbench Access is designed to be a pluggable access control system. New access
control systems should be possible by following the documentation in
workbench_access.api.php, distributed with the module.

Currently, new plugins must be loaded from the /modules folder inside the
workbench_access directory. Fixing that is on the Feature roadmap.

Note also that we do not use Field API for data storage. This decision is
deliberate for three reasons:

  -- Section data for nodes is 'stateless'. That is, it is permanent data that
  is independent of node revisions.
  -- Doing the necessary queries and joins to custom table data is easier than
  using the Field API, and likely faster.
  -- To properly integrate with Views, we need direct control over the table
  structures of our data.

However, we may consider moving to Field storage in later versions.


----
7.2   Database schema

Workbench Access creates four tables in your Drupal installation.

  -- workbench_access
  Stores data for the active access schemes on the site.

  -- workbench_access_node
  Stores the section assignments for each node.

  -- workbench_access_role
  Stores the section assignements for each role.

  -- workbench_access_user
  Stores the section assignements for each user.

See workbench_access_scheme() in workbench_access.install for table definitions.


----
7.3   Views integration

Workbench Access provides Views integration in three distinct ways.

  -- It provides the necessary fields, sort handlers, and filters for using node
  section assignments with Views.

  -- It provides a definition for menu_links table data if one is not present.
  This integration is very lightweight and only useful for sorting and filtering
  content when menu module controls the access scheme.

  -- When using the full Workbench suite, it adds a Sections filter and field to
  any View defined by Workbench modules. (These are identified by a 'Workbench'
  Views tag.)

Note that the Views integration has to alter how Views joins to taxonomy tables
when taxonomy-based sections are used.


----
8.  Feature roadmap

  -- Allows plugin registration from other modules.
  -- Allow native form elements (like taxonomy) to set access permissions.
  -- Support multiple section selection for content.
  -- Support per-content-type settings for access.

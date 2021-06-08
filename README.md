# General Information

This project was built in collaboration, with the team members being:
 - Stefan Bittgen
 - Eva Grabler
 - Nikolaus Rieder

# Project Structure

Inside the Project, there's a folder structure, which contains various files as described below:
 - `src/` ... contains all project-source files, necessary to build the main application.
 - `inc/` ... contains all project-header files, used inside the source-files.
 - `tests/` ... contains all unit-test-source files, which test code-coverage of the project using the Google Framework `gtest`
 - `modules/` ... contains the cmake-files which are required by the Google Test Framework.
 - `cmake-build/` ... is the output-directory for building the project. Also contains a README on how to build the project.
 
 Further below is an explanation on how to build the project.

 # Info on Requirements-Linking to Code

 In our collaboration we tried to use many of the provided Features in GitLab to track our Requirements.
 We might not have done a perfect job, since it was a learning experience from the start, but we've tried to make it traceable.

 Either commits/mergeRequests are directly linked in the requirements or there is at least a comment in the requirement, which does so.

 Late in the development process we've also created some implementation-issues, which describe certain features that were left over to implement, after the initial codebase was written.

 To view all completed project requirements, use this link:
 https://es.technikum-wien.at/bic/bic2_hwse2_2021/6/-/issues?scope=all&utf8=%E2%9C%93&state=closed

 Our requirements are all labeled with the corresponding Requirement-Category (Yellow labels) and also with the corresponding Feature-Category (Green labels). By selecting those labels in the search-bar, the issues can be filtered.
Some features, which were implemented later in the project, were created based on Implementation-issues (Orange labels).

# How to build the project

Included in this project is a Makefile and a CMakeLists. 
Since the makefile includes targes for cmake, it is optional to use cmake directly.
It is recommended to use the provided Makefile, as it correctly uses the provided output-folder `cmake-build`.

TBD

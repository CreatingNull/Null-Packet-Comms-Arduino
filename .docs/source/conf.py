# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html
# -- Path setup --------------------------------------------------------------
# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import subprocess
from re import match
from configparser import ConfigParser

if os.environ.get('READTHEDOCS', None) == 'True':
    # We are building live docs, doxygen needs to be run first.
    subprocess.call('cd ../doxygen; doxygen', shell=True)


# -- Project information -----------------------------------------------------

# Load from library.properties
parser = ConfigParser()
with open(os.path.abspath("../../library.properties")) as stream:
    # You can add a dummy section to use config parser for reading this file.
    parser.read_string("[Arduino]\n" + stream.read())

project = "Null Packet Comms Arduino"
author = parser["Arduino"]["author"]
copyright = f"2023, {author}"
__version__ = parser["Arduino"]["version"]

# The short MAJOR.MINOR version.
version = match(r"^[\d].[\d]", __version__).group(0)
# The full version, including alpha/beta/rc tags.
release = __version__

# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = ["breathe"]
master_doc = "index"

# Setup the breathe extension
breathe_projects = {
    "NullPacketComms": "../doxygen/xml"
}
breathe_default_project = "NullPacketComms"

# Tell sphinx what the primary language being documented is.
primary_domain = 'cpp'

# Tell sphinx what the pygments highlight language should be.
highlight_language = 'cpp'

# Add any paths that contain templates here, relative to this directory.
templates_path = ["_templates"]

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ["_build", "Thumbs.db", ".DS_Store"]

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = "sphinx_rtd_theme"
html_logo = "https://raw.githubusercontent.com/CreatingNull/NullTek-Assets/main/img/logo/NullTekDocumentationLogo.png"


# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = [""]

CRITERION_VER=$(brew info criterion | awk '{for (I=1;I<=NF;I++) if ($I == "stable") {print $(I+1)};}' | sed -e 's/^"//' -e 's/,$//')
export LIBRARY_PATH=$LIBRARY_PATH:$HOME/.brew/Cellar/criterion/$CRITERION_VER/lib/
export CPATH=$CPATH:$HOME/.brew/Cellar/criterion/$CRITERION_VER/include/

[![codecov](https://codecov.io/gh/nesvoboda/minishell/branch/master/graph/badge.svg)](https://codecov.io/gh/nesvoboda/minishell)
![C/C++ CI](https://github.com/nesvoboda/minishell/workflows/C/C++%20CI/badge.svg?event=push)
[![time tracker](https://wakatime.com/badge/github/nesvoboda/minishell.svg)](https://wakatime.com/badge/github/nesvoboda/minishell)

WIP by ablanar and ashishae

# Running the tests

## Install criterion

### [Criterion](https://github.com/Snaipe/Criterion)
Mac OS:
```brew install snaipe/soft/criterion```

#### 42 clusters 
If you are installing Criterion in a 42 cluster, you should also source `set_env.sh` to add this library to GCC's library and includes search path:

```source ./set_env.sh```

You probably should source this script from your shell config (i.e. `~/.bashrc` or `~/.zshrc`)

Other installation methods: https://github.com/Snaipe/Criterion


## Run the tests

`make run_tests`

# Test suite of weserv/images

Tests are automatically run on GitHub Actions (using
[this configuration](../.github/workflows/ci.yml)) whenever new commits are
made to the repository or when new pull requests are opened. If something
breaks, you'll be informed by GitHub.

The unit test cases are written using
[Catch2](https://github.com/catchorg/Catch2) as C++ test framework. We use the
[Test::Nginx](https://metacpan.org/pod/Test::Nginx::Socket) Perl test
scaffolding for the integration tests. Consult the previous links for
information on how to extend the tests.

## Dependencies

The test suite is run with GitHub Actions but can also be run manually, the
following dependencies are required to run the unit tests:

* libvips version >= 8.12

Other dependencies (such as [Catch2](https://github.com/catchorg/Catch2)) will
be automatically downloaded and built if they are not already present.

For the integration tests you need the following dependencies:

* Nginx version >= 1.9.11

* Perl modules:
    * [Test::Nginx](https://metacpan.org/pod/Test::Nginx::Socket)

* Nginx modules:
    * ngx_weserv (i.e., this module)

## Unit tests

To run the unit tests:

```bash
git clone https://github.com/weserv/images.git
cd images
meson setup build -Dbuildtype=debug -Dtests=true
meson compile -C build
meson test -C build
```

## Integration tests

To run the integration tests in the default testing mode:

```bash
export PATH="/usr/local/nginx/sbin:$PATH"
TEST_NGINX_SERVROOT="$PWD/servroot" prove -I/path/to/test-nginx/lib -r test/nginx
```

This assumes that Nginx along with the weserv module is already installed,
see [INSTALL.md](../INSTALL.md) for details.

To run specific test files:

```bash
export PATH="/usr/local/nginx/sbin:$PATH"
prove -I/path/to/test-nginx/lib test/nginx/file.t test/nginx/proxy.t
```

To run a specific test block in a particular test file, add the line
`--- ONLY` to the test block you want to run, and then use the `prove`
utility to run that `.t` file.

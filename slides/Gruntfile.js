/* global module:false */
module.exports = function(grunt) {
    var port = grunt.option('port') || 8000;
    // Project configuration
    grunt.initConfig({
        pkg: grunt.file.readJSON('reveal.js/package.json'),
        meta: {
            banner:
                '/*!\n' +
                ' * reveal.js <%= pkg.version %> (<%= grunt.template.today("yyyy-mm-dd, HH:MM") %>)\n' +
                ' * http://lab.hakim.se/reveal-js\n' +
                ' * MIT licensed\n' +
                ' *\n' +
                ' * Copyright (C) 2015 Hakim El Hattab, http://hakim.se\n' +
                ' */'
        },

        qunit: {
            files: [ 'test/*.html' ]
        },

        uglify: {
            options: {
                banner: '<%= meta.banner %>\n'
            },
            build: {
                src: 'js/reveal.js',
                dest: 'js/reveal.min.js'
            }
        },

        sass: {
            core: {
                files: {
                    'reveal.js/css/reveal.css': 'reveal.js/css/reveal.scss',
                }
            },
            themes: {
                files: {
                    'reveal.js/css/theme/black.css': 'reveal.js/css/theme/source/black.scss',
                    'reveal.js/css/theme/white.css': 'reveal.js/css/theme/source/white.scss',
                    'reveal.js/css/theme/league.css': 'reveal.js/css/theme/source/league.scss',
                    'reveal.js/css/theme/beige.css': 'reveal.js/css/theme/source/beige.scss',
                    'reveal.js/css/theme/night.css': 'reveal.js/css/theme/source/night.scss',
                    'reveal.js/css/theme/serif.css': 'reveal.js/css/theme/source/serif.scss',
                    'reveal.js/css/theme/simple.css': 'reveal.js/css/theme/source/simple.scss',
                    'reveal.js/css/theme/sky.css': 'reveal.js/css/theme/source/sky.scss',
                    'reveal.js/css/theme/moon.css': 'reveal.js/css/theme/source/moon.scss',
                    'reveal.js/css/theme/solarized.css': 'reveal.js/css/theme/source/solarized.scss',
                    'reveal.js/css/theme/blood.css': 'reveal.js/css/theme/source/blood.scss'
                }
            }
        },

        autoprefixer: {
            dist: {
                src: 'reveal.js/css/reveal.css'
            }
        },

        cssmin: {
            compress: {
                files: {
                    'reveal.js/css/reveal.min.css': [ 'reveal.js/css/reveal.css' ]
                }
            }
        },

        jshint: {
            options: {
                curly: false,
                eqeqeq: true,
                immed: true,
                latedef: true,
                newcap: true,
                noarg: true,
                sub: true,
                undef: true,
                eqnull: true,
                browser: true,
                expr: true,
                globals: {
                    head: false,
                    module: false,
                    console: false,
                    unescape: false,
                    define: false,
                    exports: false
                }
            },
            files: [ 'Gruntfile.js', 'reveal.js/js/reveal.js' ]
        },

        connect: {
            server: {
                options: {
                    port: port,
                    base: '.',
                    livereload: true,
                    open: true
                }
            }
        },

        zip: {
            'reveal-js-presentation.zip': [
                'index.html',
                'reveal.js/css/**',
                'reveal.js/js/**',
                'reveal.js/lib/**',
                'reveal.js/images/**',
                'reveal.js/plugin/**'
            ]
        },

        watch: {
            options: {
                livereload: true
            },
            js: {
                files: [ 'Gruntfile.js', 'reveal.js/js/reveal.js' ],
                tasks: 'js'
            },
            theme: {
                files: [ 'reveal.js/css/theme/source/*.scss', 'reveal.js/css/theme/template/*.scss' ],
                tasks: 'css-themes'
            },
            css: {
                files: [ 'reveal.js/css/reveal.scss' ],
                tasks: 'css-core'
            },
            html: {
                files: [ 'index.html']
            }
        }

    });

    // Dependencies
    grunt.loadNpmTasks( 'grunt-contrib-qunit' );
    grunt.loadNpmTasks( 'grunt-contrib-jshint' );
    grunt.loadNpmTasks( 'grunt-contrib-cssmin' );
    grunt.loadNpmTasks( 'grunt-contrib-uglify' );
    grunt.loadNpmTasks( 'grunt-contrib-watch' );
    grunt.loadNpmTasks( 'grunt-sass' );
    grunt.loadNpmTasks( 'grunt-contrib-connect' );
    grunt.loadNpmTasks( 'grunt-autoprefixer' );
    grunt.loadNpmTasks( 'grunt-zip' );

    // Default task
    grunt.registerTask( 'default', [ 'css', 'js' ] );

    // JS task
    grunt.registerTask( 'js', [ 'jshint', 'uglify', 'qunit' ] );

    // Theme CSS
    grunt.registerTask( 'css-themes', [ 'sass:themes' ] );

    // Core framework CSS
    grunt.registerTask( 'css-core', [ 'sass:core', 'autoprefixer', 'cssmin' ] );

    // All CSS
    grunt.registerTask( 'css', [ 'sass', 'autoprefixer', 'cssmin' ] );

    // Package presentation to archive
    grunt.registerTask( 'package', [ 'default', 'zip' ] );

    // Serve presentation locally
    grunt.registerTask( 'serve', [ 'connect', 'watch' ] );

    // Run tests
    grunt.registerTask( 'test', [ 'jshint', 'qunit' ] );

};

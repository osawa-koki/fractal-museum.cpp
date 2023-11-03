import React from 'react'
import { type AppProps } from 'next/app'
import Head from 'next/head'

import 'bootstrap/dist/css/bootstrap.min.css'
import '../styles/style.scss'
import '../styles/menu.scss'

import setting from '../setting'
import Layout from '../components/Layout'

export default function MyApp ({ Component, pageProps }: AppProps): React.JSX.Element {
  return (
    <>
      <Head>
        <meta charSet='utf-8' />
        <title>{setting.title}</title>
        <meta name='viewport' content='initial-scale=1.0, width=device-width' />
        <link
          rel='icon'
          type='image/png'
          href={`${setting.basePath}/favicon.ico`}
        />
      </Head>
      <Layout>
        <Component {...pageProps} />
      </Layout>
    </>
  )
}
